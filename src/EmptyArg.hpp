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
		const ParseResult ParseOperandAndSetDefined(std::optional<std::string> nextArg, bool& usedNextArg) override;
		const ParseResult ParseLongOperandAndSetDefined(std::optional<std::string> nextArg, bool& usedNextArg) override;
	};

}