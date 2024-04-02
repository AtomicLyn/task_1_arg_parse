#include "MultiBoolArg.hpp"
#include "Helpers.hpp"

using namespace args_parse;

MultiBoolArg::MultiBoolArg(const char option, std::string longOption, std::string description) : Arg(ArgumentType::MultiBool, option, longOption, description) {};

const std::vector<bool> MultiBoolArg::GetValues() {
	return values;
}

const int MultiBoolArg::GetCount() {
	return values.size();
}

const ParseResult MultiBoolArg::Parse(std::string_view arg) {
	if (const auto result = ParseOption(arg); result.IsOk()) {

		if (isInteger(operands)) {
			const auto num = atoi(operands.c_str());

			if (num == 0 || num == 1) {
				values.push_back(num == 1);

				isDefined = true;

				return ParseResult::Ok();
			}
			else ParseResult::Fail({ "In " + std::string(arg) + ": The option is found, but the value is not bool (0 or 1)" });
		}
		else return ParseResult::Fail({ "In " + std::string(arg) + ": The option is found, but the value is not integer" });
	}
	else return ParseResult::Ok();
}

const ParseResult MultiBoolArg::ParseLong(std::string_view arg) {
	if (const auto result = ParseLongOption(arg); result.IsOk()) {

		if (isInteger(operands)) {
			const auto num = atoi(operands.c_str());

			if (num == 0 || num == 1) {
				values.push_back(num == 1);

				isDefined = true;

				return ParseResult::Ok();
			}
			else ParseResult::Fail({ "In " + std::string(arg) + ": The option is found, but the value is not bool (0 or 1)" });
		}
		else return ParseResult::Fail({ "In " + std::string(arg) + ": The option is found, but the value is not integer" });
	}
	else return ParseResult::Ok();
}