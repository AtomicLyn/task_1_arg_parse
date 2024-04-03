#pragma once

#include "Arg.hpp"
#include "ArgumentType.hpp"

namespace args_parse {
	/**
	* @brief Класс пустого аргумента
	* Аргумент не содержит ничего, кроме опции
	*/

	class EmptyArg : public Arg {
	public:
		EmptyArg(const char option, std::string longOption, std::string description = "");
		const ParseResult Parse(std::string_view arg) override;
		const ParseResult ParseLong(std::string_view arg) override;
	};

}