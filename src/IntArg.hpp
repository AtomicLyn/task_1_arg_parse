#pragma once

#include "Arg.hpp"
#include <memory>
#include "Validators.hpp"

namespace args_parse {
	/**
	* @brief Класс целочисленного аргумента
	* Аргумент содержит опцию и целочисленный операнд
	*/

	class IntArg : public Arg {
		std::unique_ptr<IntValidator*> validator;
		int value = -1; ///< Поле, хранящее значение аргумента в случае успешного парсинга
	public:
		IntArg(IntValidator* validator, const char option, std::string longOption, std::string description = "");
		const int GetValue(); ///< Геттер для value
		const ParseResult Parse(std::string_view arg) override;
		const std::pair<ParseResult, int> ParseLong(std::string_view arg) override;
	};

}