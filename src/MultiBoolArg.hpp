#pragma once

#include "Arg.hpp"
#include <vector>

namespace args_parse {
	/**
	* @brief Класс мультибулевого аргумента
	* Аргумент содержит опцию и набор булевых операндов
	*/

	class MultiBoolArg : public Arg {
	private:
		/// Поле, хранящее значения аргумента в случае успешного парсинга 
		/// @warning Может быть передано несколько одинаковых аргументов командной строки
		std::vector<bool> values;
	public:
		MultiBoolArg(const char option, std::string longOption, std::string description = "");
		const std::vector<bool> GetValues(); ///< Геттер для values
		const bool Parse(std::string_view arg) override;
		const bool ParseLong(std::string_view arg) override;
	};

}