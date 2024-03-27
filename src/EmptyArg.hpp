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
		bool Parse(const char* arg) override;
		bool ParseLong(const char* arg) override;
	};

}