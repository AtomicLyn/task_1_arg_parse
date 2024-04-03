#include "StringArg.hpp"

using namespace args_parse;

StringArg::StringArg(const char option, std::string longOption, std::string description) : Arg(ArgumentType::String, option, longOption, description) {};

const std::string StringArg::GetValue() {
	return value;
}


const ParseResult StringArg::Parse(std::string_view arg) {
	if (const auto result = ParseOption(arg); result.IsOk()) {
		value = operands;

		isDefined = true;

		return ParseResult::Ok();
	}
	else return result;
}

const ParseResult StringArg::ParseLong(std::string_view arg) {
	if (const auto result = ParseLongOption(arg); result.IsOk()) {
		value = operands;

		isDefined = true;

		return ParseResult::Ok();
	}
	else return result;
}

