#pragma once

#include "Arg.hpp"
#include <vector>

namespace args_parse {
	/**
	* @brief Класс парсера аргументов командной строки
	* Возможные варианты парсинга:
	* -c
	* -cd
	* -c10
	* -c=10
	* -c 10
	* --check=10
	* --check 10
	*/

	class ArgParser {
		std::vector<Arg*> arguments;
		[[nodiscard]] const bool ParseSubsequence(std::string_view argumentWithoutDash);
	public:
		void Add(Arg* argument);
		[[nodiscard]] const bool Parse(const int argc, const char** argv);
		const std::string GetHelp() const;
	};
}
