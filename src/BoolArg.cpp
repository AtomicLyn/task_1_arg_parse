#include "BoolArg.hpp"
#include "Helpers.hpp"

using namespace args_parse;

BoolArg::BoolArg(const char option, std::string longOption, std::string description) : Arg(ArgumentType::Bool, option, longOption, description) {};

const bool BoolArg::GetValue() {
	return value;
}

const ParseResult BoolArg::ParseOperandAndSetDefined() {
	if (isInteger(operands)) {
		const auto num = atoi(operands.c_str());

		if (const auto valResult = validator.Check(num); valResult.IsOk()) {
			value = num == 1;

			isDefined = true;

			return ParseResult::Ok();
		}
		else return valResult;
	}
	else return ParseResult::Fail({ "In " + currentArg + ": The option is found, but the value is not integer" });
}

const ParseResult BoolArg::ParseLongOperandAndSetDefined() {
	if (operands[0] != '=') return ParseResult::Fail({ "In " + currentArg + ": Symbol '=' or space between option and operand was not found" });
	if (operands.size() <= 1) return ParseResult::Fail({ "In " + currentArg + ": Symbol '='  was found, but there is no value" });

	operands = operands.substr(1);

	if (!isInteger(operands)) return ParseResult::Fail({ "In " + currentArg + ": The option is found, but the value is not integer" });

	const auto num = atoi(operands.c_str());

	if (const auto valResult = validator.Check(num); valResult.IsOk()) {
		value = num == 1;

		isDefined = true;

		return ParseResult::Ok();
	}
	else return valResult;
}