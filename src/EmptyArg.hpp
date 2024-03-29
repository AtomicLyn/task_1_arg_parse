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
		EmptyArg(const char option, const char* longOption, const char* description = "");
		bool Parse(std::string_view arg) override;
		bool ParseLong(std::string_view arg) override;
	};

}