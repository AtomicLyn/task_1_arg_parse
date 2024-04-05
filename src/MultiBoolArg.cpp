#include "MultiBoolArg.hpp"
#include "Helpers.hpp"

using namespace args_parse;

MultiBoolArg::MultiBoolArg(const char option, std::string longOption, std::string description) : Arg(ArgumentType::MultiBool, option, longOption, description) {};

const std::vector<bool> MultiBoolArg::GetValues() {
	return values;
}

const int MultiBoolArg::GetCount() {
	return values.size();
}

const ParseResult MultiBoolArg::ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;

	if (!isInteger(operands))
		return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + " : The option is found, but the value is not integer" });

	const auto num = atoi(operands.c_str());

	if (const auto valResult = validator.Check(num); !valResult.IsOk()) return valResult;

	values.push_back(num == 1);
	isDefined = true;

	return ParseResult::Ok();

}

const ParseResult MultiBoolArg::ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;

	if (!isInteger(operands))
		return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + " : The option is found, but the value is not integer" });

	const auto num = atoi(operands.c_str());

	if (const auto valResult = validator.Check(num); !valResult.IsOk()) return valResult;

	values.push_back(num == 1);
	isDefined = true;

	return ParseResult::Ok();
}