#pragma once

#include "Arg.hpp"

namespace args_parse {
	/**
	* @brief Класс строкового аргумента
	* Аргумент содержит опцию и строковый операнд
	*/

	class StringArg : public Arg {
	private:
		std::string value = "";
	public:
		StringArg(const char option, std::string longOption, std::string description = "");
		const std::string GetValue();
		const bool Parse(std::string_view option) override;
		const bool ParseLong(std::string_view option) override;
	};

}