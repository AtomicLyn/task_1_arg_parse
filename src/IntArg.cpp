#include "IntArg.hpp"
#include "Helpers.hpp"

using namespace args_parse;

IntArg::IntArg(IntValidator* validator, const char option, std::string longOption, std::string description)
	: validator{ std::make_unique<IntValidator*>(std::move(validator)) }, Arg(ArgumentType::Int, option, longOption, description) {};

const int IntArg::GetValue() {
	return value;
}

const ParseResult IntArg::ParseOperandAndSetDefined() {
	if (!isInteger(operands)) return ParseResult::Fail({ "In " + currentArg + ": The option is found, but the value is not integer" });

	const auto num = atoi(operands.c_str());

	if (const auto valResult = (*validator)->Check(num); valResult.IsOk()) {
		value = num;

		isDefined = true;

		return ParseResult::Ok();
	}
	else return valResult;
}

const ParseResult IntArg::ParseLongOperandAndSetDefined() {
	if (operands[0] != '=') return ParseResult::Fail({ "In " + currentArg + ": Symbol '=' or space between option and operand was not found" });
	if (operands.size() <= 1) return ParseResult::Fail({ "In " + currentArg + ": Symbol '='  was found, but there is no value" });

	operands = operands.substr(1);

	if (!isInteger(operands)) return ParseResult::Fail({ "In " + currentArg + ": The option is found, but the value is not integer" });

	const auto num = atoi(operands.c_str());

	if (const auto valResult = (*validator)->Check(num); valResult.IsOk()) {
		value = num;

		isDefined = true;

		return ParseResult::Ok();
	}
	else return valResult;
}