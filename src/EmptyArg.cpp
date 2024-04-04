#include "EmptyArg.hpp"

using namespace args_parse;

EmptyArg::EmptyArg(const char option, std::string longOption, std::string description) : Arg(ArgumentType::Empty, option, longOption, description) {};

const ParseResult EmptyArg::ParseOperandAndSetDefined() {
	isDefined = true;

	return ParseResult::Ok();
}

const ParseResult EmptyArg::ParseLongOperandAndSetDefined() {

	isDefined = true;

	return ParseResult::Ok();
}

