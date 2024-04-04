#include "EmptyArg.hpp"

using namespace args_parse;

EmptyArg::EmptyArg(const char option, std::string longOption, std::string description) : Arg(ArgumentType::Empty, option, longOption, description) {};

const ParseResult EmptyArg::ParseOperandAndSetDefined() {
	isDefined = true;

	return ParseResult::Ok();
}

const ParseResult EmptyArg::ParseLongOperandAndSetDefined() {
	if (operands[0] != '=') return ParseResult::Fail({ "In " + currentArg + ": Symbol '=' or space between option and operand was not found" });
	if (operands.size() <= 1) return ParseResult::Fail({ "In " + currentArg + ": Symbol '='  was found, but there is no value" });

	isDefined = true;

	return ParseResult::Ok();
}

