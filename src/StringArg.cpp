#include "StringArg.hpp"

using namespace args_parse;

StringArg::StringArg(StringValidator* validator, const char option, std::string longOption, std::string description)
	: validator{ std::make_unique<StringValidator*>(std::move(validator)) }, Arg(ArgumentType::String, option, longOption, description) {};

const std::string StringArg::GetValue() {
	return value;
}


const ParseResult StringArg::SetDefinedAndParseOperand(std::string_view arg) {
	if (const auto result = ParseOption(arg); result.IsOk()) {
		
		if (const auto valResult = (*validator)->Check(operands); valResult.IsOk()) {
			value = operands;

			isDefined = true;

			return ParseResult::Ok();
		}
		else return valResult;
	}
	else return result;
}

const std::pair<ParseResult, int> StringArg::SetDefinedAndParseLongOperand(std::string_view arg) {
	if (const auto result = ParseLongOption(arg); result.first.IsOk()) {
		
		if (const auto valResult = (*validator)->Check(operands); valResult.IsOk()) {
			value = operands;

			isDefined = true;

			return std::make_pair(ParseResult::Ok(), result.second);
		}
		else return std::make_pair(valResult, result.second);
	}
	else return result;
}

