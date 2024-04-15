#pragma once

#include <thread>
#include <vector>
#include <filesystem>
#include <list>

namespace scan_dir {

	class Directory {
		std::thread::id threadId;
		std::filesystem::path filepath;
		std::vector<std::string> filenames;
		std::list<Directory> directories;
	public:
		Directory& AddAndGet();
		void Show(const int whitespace = 1);
	};

}