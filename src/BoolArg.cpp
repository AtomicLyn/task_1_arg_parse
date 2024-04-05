#include "BoolArg.hpp"
#include "Helpers.hpp"

using namespace args_parse;

BoolArg::BoolArg(const char option, std::string longOption, std::string description) : Arg(ArgumentType::Bool, option, longOption, description) {};

const bool BoolArg::GetValue() {
	return value;
}

const ParseResult BoolArg::ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;

	if (!isInteger(operands))
		return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + " : The option is found, but the value is not integer"});

	const auto num = atoi(operands.c_str());

	if (const auto valResult = validator.Check(num); !valResult.IsOk()) return valResult;

	value = num == 1;
	isDefined = true;

	return ParseResult::Ok();
}

const ParseResult BoolArg::ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;

	if (!isInteger(operands))
		return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + " : The option is found, but the value is not integer"});

	const auto num = atoi(operands.c_str());

	if (const auto valResult = validator.Check(num); !valResult.IsOk()) return valResult;

	value = num == 1;
	isDefined = true;

	return ParseResult::Ok();
}