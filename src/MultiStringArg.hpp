#pragma once

#include "Arg.hpp"
#include <vector>
#include <string>

namespace args_parse {
	/**
	* @brief Класс мультистрокового аргумента
	* Аргумент содержит опцию и набор строковых операндов
	*/

	class MultiStringArg : public Arg {
	private:
		std::vector<std::string> values;
	public:
		MultiStringArg(const char option, const char* longOption, const char* description = "");
		std::vector<std::string> GetValues();
		bool Parse(const char* option) override;
		bool ParseLong(const char* option) override;
	};

}