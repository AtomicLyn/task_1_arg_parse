#pragma once

#include "Arg.hpp"
#include "Validators.hpp"

namespace args_parse {
	/**
	* @brief Класс булевого аргумента
	* Аргумент содержит опцию и булевый операнд
	*/
	class BoolArg : public Arg {
		const BoolValidator validator;
		bool value = false; ///< Поле, хранящее значение аргумента в случае успешного парсинга
	public: 
		BoolArg(const char option, std::string longOption, std::string description = "");
		/// Геттер для value
		const bool GetValue();
		ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override;
		ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override;
	};

}