#pragma once

#include "Arg.hpp"
#include <vector>
#include <memory>
#include "Validators.hpp"

namespace args_parse {
	/**
	* @brief Класс мультицелочисленного аргумента
	* Аргумент содержит опцию и набор целочисленных операндов
	*/
	class MultiIntArg : public Arg {
		const std::unique_ptr<IntValidator> validator;
		/// Поле, хранящее значения аргумента в случае успешного парсинга 
		/// @warning Может быть передано несколько одинаковых аргументов командной строки
		std::vector<int> values;
	public:
		MultiIntArg(std::unique_ptr<IntValidator> validator, const char option, std::string longOption, std::string description = "");
		/// Геттер для values
		const std::vector<int>& GetValues() const;
		/// Количество значений в values
		const int GetCount();
		ParseResult ParseOperandAndSetDefined(std::optional<std::string> nextArg, bool& usedNextArg) override;
		ParseResult ParseLongOperandAndSetDefined(std::optional<std::string> nextArg, bool& usedNextArg) override;
	};

}