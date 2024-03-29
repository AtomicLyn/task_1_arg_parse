#pragma once

#include "Arg.hpp"

namespace args_parse {
	/**
	* @brief Класс целочисленного аргумента
	* Аргумент содержит опцию и целочисленный операнд
	*/

	class IntArg : public Arg {
	private:
		int value = -1;
	public:
		IntArg(const char option, const char* longOption, const char* description = "");
		int GetValue();
		bool Parse(std::string_view arg) override;
		bool ParseLong(std::string_view arg) override;
	};

}