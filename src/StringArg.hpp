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
		std::unique_ptr<StringValidator> validator;
		std::string value; ///< Поле, хранящее значение аргумента в случае успешного парсинга
	public:
		StringArg(std::unique_ptr<StringValidator> validator, const char option, std::string longOption, std::string description = "");
		/// Геттер для value
		std::string_view GetValue() const; 
		ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override;
		ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override;
	};

}