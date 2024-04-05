#include "EmptyArg.hpp"

using namespace args_parse;

EmptyArg::EmptyArg(const char option, std::string longOption, std::string description) : Arg(ArgumentType::Empty, option, longOption, description) {};

const ParseResult EmptyArg::ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (!operands.empty())
		if (operands[0] == '=')
			return ParseResult::Fail({ "In " + currentArg + " : Symbol '=' in EmptyArg was not expected" });

	isDefined = true;

	return ParseResult::Ok();
}

const ParseResult EmptyArg::ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (!operands.empty()) return ParseResult::Fail({ "In " + currentArg + " : The operand in EmptyArg was not expected" });

	isDefined = true;

	return ParseResult::Ok();
}

