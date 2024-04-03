#pragma once

#include "Arg.hpp"
#include "Validators.hpp"

namespace args_parse {
	/**
	* @brief Класс булевого аргумента
	* Аргумент содержит опцию и булевый операнд
	*/

	class BoolArg : public Arg {
	private:
		const BoolValidator validator;
		bool value = false; ///< Поле, хранящее значение аргумента в случае успешного парсинга
	public: 
		BoolArg(const char option, std::string longOption, std::string description = "");
		const bool GetValue(); ///< Геттер для value
		const ParseResult Parse(std::string_view arg) override;
		const ParseResult ParseLong(std::string_view arg) override;
	};

}