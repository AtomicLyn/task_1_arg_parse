#include "Directory.hpp"
#include <iostream>

using namespace scan_dir;

Directory& Directory::AddAndGet() {
	return directories.emplace_back();
}

void Directory::Show(const int whitespace) {
	std::cout << " ";
	for (auto& directory : directories) {
		std::cout << std::setw(whitespace) << directory.filepath << std::endl;
		directory.Show(whitespace + 1);
	}
	for (const auto& filename : filenames) {
		std::cout << std::setw(whitespace) << filename << std::endl;
	}
}