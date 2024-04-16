#include "Directory.hpp"
#include <iostream>

using namespace scan_dir;

Directory& Directory::AddAndGet(std::filesystem::path path) {
	return directories.emplace_back(path);
}

void Directory::Show(const int whitespace) {
	for (auto& directory : directories) {
		std::cout << std::string(whitespace, ' ') << directory.path.filename() << "(thread: " << threadId << ")/" << std::endl;
		directory.Show(whitespace + 2);
	}
	for (const auto& filename : filenames) {
		std::cout << std::string(whitespace + 2, ' ') << filename << std::endl;
	}
}