#include "StringArg.hpp"

using namespace args_parse;

StringArg::StringArg(std::unique_ptr<StringValidator> validator, const char option, std::string longOption, std::string description)
	: validator{ std::move(validator) }, Arg(ArgumentType::String, option, longOption, description) {};

std::string_view StringArg::GetValue() const {
	return value;
}


ParseResult StringArg::ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;
	if (const auto valResult = validator->Check(operands); !valResult.IsOk()) return valResult;

	value = operands;
	isDefined = true;

	return ParseResult::Ok();
}

ParseResult StringArg::ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;
	if (const auto valResult = validator->Check(operands); !valResult.IsOk()) return valResult;
	
	value = operands;
	isDefined = true;

	return ParseResult::Ok();
}

