#include "IntArg.hpp"
#include "Helpers.hpp"

using namespace args_parse;

IntArg::IntArg(IntValidator* validator, const char option, std::string longOption, std::string description)
	: validator{ std::make_unique<IntValidator*>(std::move(validator)) }, Arg(ArgumentType::Int, option, longOption, description) {};

const int IntArg::GetValue() {
	return value;
}

const ParseResult IntArg::Parse(std::string_view arg) {
	if (const auto result = ParseOption(arg); result.IsOk()) {

		if (isInteger(operands)) {
			const auto num = atoi(operands.c_str());

			if (const auto valResult = (*validator)->Check(num); valResult.IsOk()) {
				value = num;

				isDefined = true;

				return ParseResult::Ok();
			}
			else return valResult;
		}
		else return ParseResult::Fail({ "In " + std::string(arg) + ": The option is found, but the value is not integer" });
	}
	else return result;
}

const std::pair<ParseResult, int> IntArg::ParseLong(std::string_view arg) {
	if (const auto result = ParseLongOption(arg); result.first.IsOk()) {

		if (isInteger(operands)) {
			const auto num = atoi(operands.c_str());

			if (const auto valResult = (*validator)->Check(num); valResult.IsOk()) {
				value = num;

				isDefined = true;

				return std::make_pair(ParseResult::Ok(), result.second);
			}
			else return std::make_pair(valResult, result.second);
		}
		else return std::make_pair(ParseResult::Fail({ "In " + std::string(arg) + ": The option is found, but the value is not integer" }), 0);
	}
	else return result;
}