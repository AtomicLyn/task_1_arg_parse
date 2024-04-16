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
		std::mutex tasksMutex;
		std::condition_variable tasksCondVar;
		std::queue<std::reference_wrapper<Directory>> tasks;

		std::vector<std::thread> threads;

		bool isDone;
	public:
		ScanPool(std::string mainPath, int poolSize, std::chrono::microseconds debugSleep)
			: mainPath{ std::move(mainPath) }, poolSize{ poolSize }, debugSleep{ std::move(debugSleep) } {}

		~ScanPool() {
			for (auto& thread : threads) thread.join();
		}

		void Start() {

		}
	};

}