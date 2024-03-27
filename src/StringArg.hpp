#pragma once

#include "Arg.hpp"
#include <string>

namespace args_parse {
	/**
	* @brief Класс строкового аргумента
	* Аргумент содержит опцию и строковый операнд
	*/

	class StringArg : public Arg {
	private:
		std::string value = "";
	public:
		StringArg(const char option, const char* longOption, const char* description = "");
		std::string GetValue();
		bool Parse(const char* option) override;
		bool ParseLong(const char* option) override;
	};

}