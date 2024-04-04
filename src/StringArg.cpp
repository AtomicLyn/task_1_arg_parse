#include "StringArg.hpp"

using namespace args_parse;

StringArg::StringArg(StringValidator* validator, const char option, std::string longOption, std::string description)
	: validator{ std::make_unique<StringValidator*>(std::move(validator)) }, Arg(ArgumentType::String, option, longOption, description) {};

const std::string StringArg::GetValue() {
	return value;
}


const ParseResult StringArg::ParseOperandAndSetDefined() {
	if (const auto valResult = (*validator)->Check(operands); valResult.IsOk()) {
		value = operands;

		isDefined = true;

		return ParseResult::Ok();
	}
	else return valResult;
}

const ParseResult StringArg::ParseLongOperandAndSetDefined() {
	if (const auto valResult = (*validator)->Check(operands); valResult.IsOk()) {
		value = operands;

		isDefined = true;

		return ParseResult::Ok();
	}
	else return valResult;
}

