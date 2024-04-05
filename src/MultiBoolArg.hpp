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
		/// Геттер для values
		const std::vector<bool> GetValues(); 
		/// Количество значений в values
		const int GetCount(); 
		const ParseResult ParseOperandAndSetDefined() override;
		const ParseResult ParseLongOperandAndSetDefined() override;
	};

}