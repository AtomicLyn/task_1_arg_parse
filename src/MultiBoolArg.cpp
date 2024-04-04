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

const ParseResult MultiBoolArg::ParseOperandAndSetDefined() {
	if (isInteger(operands)) {
		const auto num = atoi(operands.c_str());

		if (const auto valResult = validator.Check(num); valResult.IsOk()) {
			values.push_back(num == 1);

			isDefined = true;

			return ParseResult::Ok();
		}
		else return valResult;
	}
	else return ParseResult::Fail({ "In " + std::to_string(option) + "/" + longOption + ": The option is found, but the value is not integer" });
}

const ParseResult MultiBoolArg::ParseLongOperandAndSetDefined() {
	if (isInteger(operands)) {
		const auto num = atoi(operands.c_str());

		if (const auto valResult = validator.Check(num); valResult.IsOk()) {
			values.push_back(num == 1);

			isDefined = true;

			return ParseResult::Ok();
		}
		else return valResult;
	}
	else return ParseResult::Fail({ "In " + std::to_string(option) + "/" + longOption + ": The option is found, but the value is not integer" });;
}