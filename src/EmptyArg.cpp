#include "EmptyArg.hpp"

using namespace args_parse;

EmptyArg::EmptyArg(const char option, std::string longOption, std::string description) : Arg(ArgumentType::Empty, option, longOption, description) {};

const ParseResult EmptyArg::Parse(std::string_view arg) {

	if (const auto result = ParseOption(arg); result.IsOk()) {
		isDefined = true;

		return ParseResult::Ok();
	}
	else return result;
}

const ParseResult EmptyArg::ParseLong(std::string_view arg) {

	if (const auto result = ParseLongOption(arg); result.IsOk()) {
		isDefined = true;

		return ParseResult::Ok();
	}
	else return result;
}

