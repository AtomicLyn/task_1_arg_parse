#pragma once

#include <thread>
#include <vector>
#include <filesystem>
#include <list>

namespace scan_dir {

	class Directory {
		std::thread::id threadId;
		std::filesystem::path path;
		std::vector<std::string> filenames;
		std::list<Directory> directories;
	public:
		Directory(std::filesystem::path path) : path{ path } {}
		Directory() = default;
		~Directory() = default;
		Directory& AddAndGet(std::filesystem::path path);
		void SetPath(std::filesystem::path spath) { path = spath; }
		void SetThreadId(std::thread::id id) { threadId = id; }
;		void AddFilename(std::string filename) { filenames.push_back(filename); }
		std::filesystem::path GetPath() { return path; }
		void Show(const int whitespace = 0);
	};

}