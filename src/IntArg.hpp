#pragma once

#include "Arg.hpp"

namespace args_parse {
	/**
	* @brief Класс целочисленного аргумента
	* Аргумент содержит опцию и целочисленный операнд
	*/

	class IntArg : public Arg {
	private:
		int value = -1; ///< Поле, хранящее значение аргумента в случае успешного парсинга
	public:
		IntArg(const char option, std::string longOption, std::string description = "");
		const int GetValue(); ///< Геттер для value
		const bool Parse(std::string_view arg) override;
		const bool ParseLong(std::string_view arg) override;
	};

}