#pragma once

#include "Arg.hpp"
#include "memory"
#include "Validators.hpp"

namespace args_parse {
	/**
	* @brief Класс строкового аргумента
	* Аргумент содержит опцию и строковый операнд
	*/
	class StringArg : public Arg {
		std::unique_ptr<StringValidator*> validator;
		std::string value; ///< Поле, хранящее значение аргумента в случае успешного парсинга
	public:
		StringArg(StringValidator* validator, const char option, std::string longOption, std::string description = "");
		const std::string GetValue(); ///< Геттер для value
		const ParseResult SetDefinedAndParseOperand(std::string_view arg) override;
		const std::pair<ParseResult, int> SetDefinedAndParseLongOperand(std::string_view arg) override;
	};

}