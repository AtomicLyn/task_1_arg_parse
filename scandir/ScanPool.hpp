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

		std::mutex poolM;
		std::condition_variable poolCV;

		bool isDone = false;

		void Scan(bool& isWorking, bool needToSleep = false);

	public:
		ScanPool(std::string mainPath, int poolSize, std::chrono::microseconds debugSleep);
		~ScanPool();
		const Directory& StartAndGetDirectory();

	};
}