#pragma once

#include <vector>
#include "Arg.hpp"
#include <string>

namespace args_parse {
	/**
	* @brief  ласс парсера аргументов командной строки
	* ¬озможные варианты парсинга:
	* -c
	* -cd
	* -c10
	* -c=10
	* -c 10
	* --check=10
	* --check 10
	*/
	class ArgParser {
	private:
		std::vector<Arg*> arguments;
	public:
		void Add(Arg* argument);
		bool Parse(const int argc, const char** argv);
		std::string GetHelp();
	};
}
