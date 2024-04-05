#pragma once

#include "Arg.hpp"
#include <vector>
#include <memory>
#include "Validators.hpp"

namespace args_parse {
	/**
	* @brief Класс мультистрокового аргумента
	* Аргумент содержит опцию и набор строковых операндов
	*/

	class MultiStringArg : public Arg {
		const std::unique_ptr<StringValidator*> validator;
		/// Поле, хранящее значения аргумента в случае успешного парсинга 
		/// @warning Может быть передано несколько одинаковых аргументов командной строки
		std::vector<std::string> values; 
	public:
		MultiStringArg(StringValidator* validator, const char option, std::string longOption, std::string description = "");
		/// Геттер для values
		const std::vector<std::string> GetValues(); 
		/// Количество значений в values
		const int GetCount(); 
		const ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override;
		const ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override;
	};

}