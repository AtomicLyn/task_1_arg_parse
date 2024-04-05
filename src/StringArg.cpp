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
	if (operands[0] != '=') 
		return ParseResult::Fail({ "In " + currentArg + ": Symbol '=' or space between option and operand was not found" });
	if (operands.size() <= 1) 
		return ParseResult::Fail({ "In " + currentArg + ": Symbol '=' was found, but there is no value" });

	operands = operands.substr(1);

	if (const auto valResult = (*validator)->Check(operands); valResult.IsOk()) {
		value = operands;

		isDefined = true;

		return ParseResult::Ok();
	}
	else return valResult;
}

