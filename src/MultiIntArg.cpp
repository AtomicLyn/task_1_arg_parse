#include "MultiIntArg.hpp"
#include "Helpers.hpp"

using namespace args_parse;

MultiIntArg::MultiIntArg(IntValidator* validator, const char option, std::string longOption, std::string description) 
	: validator{ std::make_unique<IntValidator*>(std::move(validator)) }, Arg(ArgumentType::MultiInt, option, longOption, description) {};

const std::vector<int> MultiIntArg::GetValues() {
	return values;
}

const int MultiIntArg::GetCount() {
	return values.size();
}

const ParseResult MultiIntArg::Parse(std::string_view arg) {
	if (const auto result = ParseOption(arg); result.IsOk()) {

		if (isInteger(operands)) {
			auto num = atoi(operands.c_str());

			if (const auto valResult = (*validator)->Check(num); valResult.IsOk()) {
				values.push_back(num);

				isDefined = true;

				return ParseResult::Ok();
			}
			else return valResult;
		}
		else return ParseResult::Fail({ "In " + std::string(arg) + ": The option is found, but the value is not integer" });
	}
	else return result;
}

const std::pair<ParseResult, int> MultiIntArg::ParseLong(std::string_view arg) {
	if (const auto result = ParseLongOption(arg); result.first.IsOk()) {

		if (isInteger(operands)) {
			auto num = atoi(operands.c_str());

			if (const auto valResult = (*validator)->Check(num); valResult.IsOk()) {
				values.push_back(num);

				isDefined = true;

				return std::make_pair(ParseResult::Ok(), result.second);
			}
			else return std::make_pair(valResult, result.second);
		}
		else return std::make_pair(ParseResult::Fail({ "In " + std::string(arg) + ": The option is found, but the value is not integer" }), result.second);
	}
	else return result;
}