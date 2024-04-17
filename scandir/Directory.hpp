#pragma once

#include <thread>
#include <vector>
#include <filesystem>
#include <list>

namespace scan_dir {
	/// @brief Класс директории, позволяющий вести обход каталога
	class Directory {
		friend class ScanPool;

		std::thread::id threadId; ///< Поле, хранящее id потока, который вел обработку текущей директории
		std::filesystem::path path; ///< Поле, хранящее путь до директории
		std::vector<std::string> filenames; ///< Поле, хранящее все файлы в текущей директории
		std::list<Directory> directories; ///< Поле, хранящее все поддиректории в текущей директории

		/// Метод для добавления пустой необработанной директории с указанным путем и получением ссылки
		Directory& AddAndGet(std::filesystem::path path) {
			return directories.emplace_back(path);
		}
		
		/// Сеттер для path
		void SetPath(std::filesystem::path spath) { path = spath; }
		/// Сеттер для threadId
		void SetThreadId(std::thread::id id) { threadId = id; }
		/// Метод добавления файла в filenames
		void AddFilename(std::string filename) { filenames.push_back(filename); }
	public:
		Directory(std::filesystem::path path) : path{ path } {}
		Directory() = default;
		~Directory() = default;
		/// Геттер для path
		std::filesystem::path GetPath() { return path; }
		/// @brief Метод для вывода содержимого директории
		/// Выполняет рекурсивный вывод всех файлов и поддиректорий из текущей директории
		void Show(const int whitespace = 0);
	};

}