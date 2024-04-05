#include "StringArg.hpp"

using namespace args_parse;

StringArg::StringArg(StringValidator* validator, const char option, std::string longOption, std::string description)
	: validator{ std::make_unique<StringValidator*>(std::move(validator)) }, Arg(ArgumentType::String, option, longOption, description) {};

const std::string StringArg::GetValue() {
	return value;
}


const ParseResult StringArg::ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;
	if (const auto valResult = (*validator)->Check(operands); !valResult.IsOk()) return valResult;

	value = operands;
	isDefined = true;

	return ParseResult::Ok();
}

const ParseResult StringArg::ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;
	if (const auto valResult = (*validator)->Check(operands); !valResult.IsOk()) return valResult;
	
	value = operands;
	isDefined = true;

	return ParseResult::Ok();
}

