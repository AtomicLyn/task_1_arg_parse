#pragma once

#include "Arg.hpp"

namespace args_parse {
	/**
	* @brief Класс строкового аргумента
	* Аргумент содержит опцию и строковый операнд
	*/

	class StringArg : public Arg {
	private:
		std::string value = ""; ///< Поле, хранящее значение аргумента в случае успешного парсинга
	public:
		StringArg(const char option, std::string longOption, std::string description = "");
		const std::string GetValue(); ///< Геттер для value
		const ParseResult Parse(std::string_view arg) override;
		const ParseResult ParseLong(std::string_view arg) override;
	};

}