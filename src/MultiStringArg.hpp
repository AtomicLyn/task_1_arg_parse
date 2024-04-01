#pragma once

#include "Arg.hpp"
#include <vector>

namespace args_parse {
	/**
	* @brief Класс мультистрокового аргумента
	* Аргумент содержит опцию и набор строковых операндов
	*/

	class MultiStringArg : public Arg {
	private:
		std::vector<std::string> values;
	public:
		MultiStringArg(const char option, std::string longOption, std::string description = "");
		const std::vector<std::string> GetValues();
		const bool Parse(std::string_view option) override;
		const bool ParseLong(std::string_view option) override;
	};

}