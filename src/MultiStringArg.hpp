#pragma once

#include "Arg.hpp"
#include <vector>

namespace args_parse {
	/**
	* @brief Класс мультистрокового аргумента
	* Аргумент содержит опцию и набор строковых операндов
	*/

	class MultiStringArg : public Arg {
	private:
		/// Поле, хранящее значения аргумента в случае успешного парсинга 
		/// @warning Может быть передано несколько одинаковых аргументов командной строки
		std::vector<std::string> values; 
	public:
		MultiStringArg(const char option, std::string longOption, std::string description = "");
		const std::vector<std::string> GetValues(); ///< Геттер для values
		const int GetCount(); ///< Количество значений в values
		const ParseResult Parse(std::string_view arg) override;
		const ParseResult ParseLong(std::string_view arg) override;
	};

}