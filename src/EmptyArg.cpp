#include "EmptyArg.hpp"

using namespace args_parse;

EmptyArg::EmptyArg(const char option, std::string longOption, std::string description) : Arg(ArgumentType::Empty, option, longOption, description) {};

const ParseResult EmptyArg::SetDefinedAndParseOperand(std::string_view arg) {

	if (const auto result = ParseOption(arg); result.IsOk()) {
		isDefined = true;

		return ParseResult::Ok();
	}
	else return result;
}

const std::pair<ParseResult, int> EmptyArg::SetDefinedAndParseLongOperand(std::string_view arg) {

	if (const auto result = ParseLongOption(arg); result.first.IsOk()) {
		isDefined = true;

		return std::make_pair(ParseResult::Ok(), result.second);
	}
	else return result;
}

