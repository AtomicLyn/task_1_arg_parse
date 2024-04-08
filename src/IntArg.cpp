#include "IntArg.hpp"
#include "Helpers.hpp"

using namespace args_parse;

IntArg::IntArg(std::unique_ptr<IntValidator> validator, const char option, std::string longOption, std::string description)
	: validator{ std::move(validator) }, Arg(ArgumentType::Int, option, longOption, description) {};

const int IntArg::GetValue() {
	return value;
}

ParseResult IntArg::ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;

	if (!isInteger(operands))
		return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + " : The option is found, but the value is not integer" });

	const auto num = atoi(operands.c_str());

	if (const auto valResult = validator->Check(num); !valResult.IsOk()) return valResult;

	value = num;
	isDefined = true;

	return ParseResult::Ok();
}

ParseResult IntArg::ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;

	if (!isInteger(operands))
		return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + " : The option is found, but the value is not integer" });

	const auto num = atoi(operands.c_str());

	if (const auto valResult = validator->Check(num); !valResult.IsOk()) return valResult;

	value = num;
	isDefined = true;

	return ParseResult::Ok();
}