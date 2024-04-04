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

const ParseResult MultiBoolArg::SetDefinedAndParseOperand(std::string_view arg) {
	if (const auto result = ParseOption(arg); result.IsOk()) {

		if (isInteger(operands)) {
			const auto num = atoi(operands.c_str());

			if (const auto valResult = validator.Check(num); valResult.IsOk()) {
				values.push_back(num == 1);

				isDefined = true;

				return ParseResult::Ok();
			}
			else return valResult;
		}
		else return ParseResult::Fail({ "In " + std::string(arg) + ": The option is found, but the value is not integer" });
	}
	else return result;
}

const std::pair<ParseResult, int> MultiBoolArg::SetDefinedAndParseLongOperand(std::string_view arg) {
	if (const auto result = ParseLongOption(arg); result.first.IsOk()) {

		if (isInteger(operands)) {
			const auto num = atoi(operands.c_str());

			if (const auto valResult = validator.Check(num); valResult.IsOk()) {
				values.push_back(num == 1);

				isDefined = true;

				return std::make_pair(ParseResult::Ok(), result.second);
			}
			else return std::make_pair(valResult, result.second);
		}
		else return std::make_pair(ParseResult::Fail({ "In " + std::string(arg) + ": The option is found, but the value is not integer" }), result.second);
	}
	else return result;
}