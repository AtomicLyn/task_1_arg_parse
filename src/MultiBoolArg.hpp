#pragma once

#include "Arg.hpp"
#include <vector>
#include "Validators.hpp"

namespace args_parse {
	/**
	* @brief Класс мультибулевого аргумента
	* Аргумент содержит опцию и набор булевых операндов
	*/
	class MultiBoolArg : public Arg {
		const BoolValidator validator;
		/// Поле, хранящее значения аргумента в случае успешного парсинга 
		/// @warning Может быть передано несколько одинаковых аргументов командной строки
		std::vector<bool> values;
	public:
		MultiBoolArg(const char option, std::string longOption, std::string description = "");
		const std::vector<bool> GetValues(); ///< Геттер для values
		const int GetCount(); ///< Количество значений в values
		const ParseResult SetDefinedAndParseOperand(std::string_view arg) override;
		const std::pair<ParseResult, int> SetDefinedAndParseLongOperand(std::string_view arg) override;
	};

}