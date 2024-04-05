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
		/// Геттер для value
		const std::string GetValue(); 
		const ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override;
		const ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override;
	};

}