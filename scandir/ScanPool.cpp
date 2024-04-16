#include "ScanPool.hpp"

using namespace scan_dir;

ScanPool::ScanPool(std::string mainPath, int poolSize, std::chrono::microseconds debugSleep)
	: mainPath{ std::move(mainPath) }, poolSize{ poolSize }, debugSleep{ std::move(debugSleep) } {}

ScanPool:: ~ScanPool() {
	isDone = true;
	for (auto& thread : threads) thread.join();
}

void ScanPool::Scan(bool& isWorking, bool needToSleep) {
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

		if (needToSleep) {
			std::this_thread::sleep_for(debugSleep);
			needToSleep = false;
		}

		{
			std::unique_lock lk{ poolM };
			isWorking = false;
			poolCV.notify_one();
		}
	}
}

const Directory& ScanPool::StartAndGetDirectory() {
	mainDirectory.SetPath(mainPath);
	tasks.push(mainDirectory);
	std::list<bool> threadsIsWorking;


	threadsIsWorking.push_back(true);
	threads.emplace_back([this, &threadsIsWorking] { Scan(threadsIsWorking.front(), true); });
	for (auto i = 1; i < poolSize; i++) {
		threadsIsWorking.push_back(false);
		threads.emplace_back([this, &threadsIsWorking] { Scan(threadsIsWorking.back()); });
	}

	std::unique_lock lk{ poolM };
	poolCV.wait(lk, [this, &threadsIsWorking] {
		return tasks.empty()
			&& std::all_of(threadsIsWorking.begin(), threadsIsWorking.end(), [](bool& t) { return !t; });
		});

	isDone = true;

	tasksCV.notify_all();

	return mainDirectory;
}