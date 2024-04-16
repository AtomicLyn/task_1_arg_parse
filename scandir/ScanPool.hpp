#pragma once

#include "Directory.hpp"
#include <filesystem>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace scan_dir {

	class ScanPool {
		std::string mainPath;
		int poolSize;
		std::chrono::microseconds debugSleep;

		Directory mainDirectory;
		std::mutex tasksM;
		std::condition_variable tasksCV;
		std::queue<std::reference_wrapper<Directory>> tasks;

		std::vector<std::thread> threads;

		bool isDone = false;

		void Scan(bool& isWorking, bool needToSleep = false) {
			Directory* currentDirectory;

			for (;;) {
				{
					std::unique_lock lk{ tasksM };
					tasksCV.wait(lk, [this]() { return !tasks.empty() || isDone; });

					if (isDone) break;

					currentDirectory = &(tasks.front().get());
					tasks.pop();

					isWorking = true;

					tasksCV.notify_one();
				}

				currentDirectory->SetThreadId(std::this_thread::get_id());
				
				for (const auto& dirEntry : std::filesystem::directory_iterator{ currentDirectory->GetPath() }) {
					if (dirEntry.is_regular_file()) currentDirectory->AddFilename(dirEntry.path().filename().string());
					else if (dirEntry.is_directory()) {
						Directory& dirRef = currentDirectory->AddAndGet(dirEntry.path());

						{
							std::unique_lock lk{ tasksM };
							tasks.push(dirRef);
							tasksCV.notify_one();
						}
					}
				}

				{
					std::unique_lock lk{ tasksM };
					isWorking = false;
					tasksCV.notify_all();
				}

				if (needToSleep) {
					std::this_thread::sleep_for(debugSleep);
					needToSleep = false;
				}
			}
		}

	public:
		ScanPool(std::string mainPath, int poolSize, std::chrono::microseconds debugSleep)
			: mainPath{ std::move(mainPath) }, poolSize{ poolSize }, debugSleep{ std::move(debugSleep) } {}

		~ScanPool() {
			isDone = true;
			for (auto& thread : threads) thread.join();
		}

		void Start() {
			mainDirectory.SetPath(mainPath);
			tasks.push(mainDirectory);
			std::list<bool> threadsIsWorking;

			threadsIsWorking.push_back(true);
			threads.emplace_back([this, &threadsIsWorking] { Scan(threadsIsWorking.back(), true); });
			for (auto i = 1; i < poolSize; i++) {
				threadsIsWorking.push_back(false);
				threads.emplace_back([this, &threadsIsWorking] { Scan(threadsIsWorking.back()); });
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(100));

			isDone = true;

			tasksCV.notify_all();

			mainDirectory.Show();
		}
	};

}