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

const ParseResult MultiIntArg::ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;

	if (!isInteger(operands))
		return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + ": The option is found, but the value is not integer" });

	auto num = atoi(operands.c_str());

	if (const auto valResult = (*validator)->Check(num); !valResult.IsOk()) return valResult;

	values.push_back(num);
	isDefined = true;

	return ParseResult::Ok();
}

const ParseResult MultiIntArg::ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;

	if (!isInteger(operands))
		return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + ": The option is found, but the value is not integer" });

	auto num = atoi(operands.c_str());

	if (const auto valResult = (*validator)->Check(num); !valResult.IsOk()) return valResult;

	values.push_back(num);
	isDefined = true;

	return ParseResult::Ok();
}