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
	private:
		const std::unique_ptr<IntValidator*> validator;
		/// Поле, хранящее значения аргумента в случае успешного парсинга 
		/// @warning Может быть передано несколько одинаковых аргументов командной строки
		std::vector<int> values;
	public:
		MultiIntArg(IntValidator* validator, const char option, std::string longOption, std::string description = "");
		const std::vector<int> GetValues(); ///< Геттер для values
		const int GetCount(); ///< Количество значений в values
		const ParseResult Parse(std::string_view arg) override;
		const ParseResult ParseLong(std::string_view arg) override;
	};

}