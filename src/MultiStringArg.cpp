#include "MultiStringArg.hpp"

using namespace args_parse;

MultiStringArg::MultiStringArg(StringValidator* validator, const char option, std::string longOption, std::string description) 
	: validator{ std::make_unique<StringValidator*>(std::move(validator)) }, Arg(ArgumentType::MultiString, option, longOption, description) {};

const std::vector<std::string> MultiStringArg::GetValues() {
	return values;
}

const int MultiStringArg::GetCount() {
	return values.size();
}

const ParseResult MultiStringArg::Parse(std::string_view arg) {
	if (const auto result = ParseOption(arg); result.IsOk()) {

		if (const auto valResult = (*validator)->Check(operands); valResult.IsOk()) {
			values.push_back(operands);

			isDefined = true;

			return ParseResult::Ok();
		}
		else return valResult;
	}
	else return result;
}

const std::pair<ParseResult, int> MultiStringArg::ParseLong(std::string_view arg) {
	if (const auto result = ParseLongOption(arg); result.first.IsOk()) {
		if (const auto valResult = (*validator)->Check(operands); valResult.IsOk()) {
			values.push_back(operands);

			isDefined = true;

			return std::make_pair(ParseResult::Ok(), result.second);
		}
		else return std::make_pair(valResult, result.second);
	}
	else return result;
}

