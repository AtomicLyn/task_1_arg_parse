#include "IntArg.hpp"
#include "Helpers.hpp"

using namespace args_parse;

IntArg::IntArg(IntValidator* validator, const char option, std::string longOption, std::string description)
	: validator{ std::make_unique<IntValidator*>(std::move(validator)) }, Arg(ArgumentType::Int, option, longOption, description) {};

const int IntArg::GetValue() {
	return value;
}

const ParseResult IntArg::ParseOperandAndSetDefined() {
	if (isInteger(operands)) {
		const auto num = atoi(operands.c_str());

		if (const auto valResult = (*validator)->Check(num); valResult.IsOk()) {
			value = num;

			isDefined = true;

			return ParseResult::Ok();
		}
		else return valResult;
	}
	else return ParseResult::Fail({ "In " + std::to_string(option) + "/" + longOption + ": The option is found, but the value is not integer" });
}

const ParseResult IntArg::ParseLongOperandAndSetDefined() {
	if (isInteger(operands)) {
		const auto num = atoi(operands.c_str());

		if (const auto valResult = (*validator)->Check(num); valResult.IsOk()) {
			value = num;

			isDefined = true;

			return ParseResult::Ok();
		}
		else return valResult;
	}
	else return ParseResult::Fail({ "In " + std::to_string(option) + "/" + longOption + ": The option is found, but the value is not integer" });
}