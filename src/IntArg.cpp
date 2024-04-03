#include "IntArg.hpp"
#include "Helpers.hpp"

using namespace args_parse;

IntArg::IntArg(const char option, std::string longOption, std::string description) : Arg(ArgumentType::Int, option, longOption, description) {};

const int IntArg::GetValue() {
	return value;
}

const ParseResult IntArg::Parse(std::string_view arg) {
	if (const auto result = ParseOption(arg); result.IsOk()) {

		if (isInteger(operands)) {
			value = atoi(operands.c_str());

			isDefined = true;

			return ParseResult::Ok();
		}
		else return ParseResult::Fail({ "In " + std::string(arg) + ": The option is found, but the value is not integer" });
	}
	else return result;
}

const ParseResult IntArg::ParseLong(std::string_view arg) {
	if (const auto result = ParseLongOption(arg); result.IsOk()) {

		if (isInteger(operands)) {
			value = atoi(operands.c_str());

			isDefined = true;

			return ParseResult::Ok();
		}
		else return ParseResult::Fail({ "In " + std::string(arg) + ": The option is found, but the value is not integer" });
	}
	else return result;
}