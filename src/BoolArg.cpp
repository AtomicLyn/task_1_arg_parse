#include "BoolArg.hpp"
#include "Helpers.hpp"

using namespace args_parse;

BoolArg::BoolArg(const char option, std::string longOption, std::string description) : Arg(ArgumentType::Bool, option, longOption, description) {};

const bool BoolArg::GetValue() {
	return value;
}

const ParseResult BoolArg::Parse(std::string_view arg) {
	if (const auto result = ParseOption(arg); result.IsOk()) {

		if (isInteger(operands)) {
			const auto num = atoi(operands.c_str());

			if (num == 0 || num == 1) {
				value = num == 1;

				isDefined = true;

				return result;
			}
			else ParseResult::Fail({ "In " + std::string(arg) + ": The option is found, but the value is not bool (0 or 1)" });
		}
		else return ParseResult::Fail({ "In " + std::string(arg) + ": The option is found, but the value is not integer" });
	}
	else return ParseResult::Ok();
}

const ParseResult BoolArg::ParseLong(std::string_view arg) {
	if (const auto result = ParseLongOption(arg); result.IsOk()) {

		if (isInteger(operands)) {
			const auto num = atoi(operands.c_str());

			if (num == 0 || num == 1) {
				value = num == 1;

				isDefined = true;

				return ParseResult::Ok();
			}
			else ParseResult::Fail({ "In " + std::string(arg) + ": The option is found, but the value is not bool (0 or 1)" });
		}
		else return ParseResult::Fail({ "In " + std::string(arg) + ": The option is found, but the value is not integer" });
	}
	else return ParseResult::Ok();
}