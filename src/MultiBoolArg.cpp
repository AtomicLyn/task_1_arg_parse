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
	if (!isInteger(operands)) 
		return ParseResult::Fail({ "In " + currentArg + ": The option is found, but the value is not integer" });

	const auto num = atoi(operands.c_str());

	if (const auto valResult = validator.Check(num); valResult.IsOk()) {
		values.push_back(num == 1);

		isDefined = true;

		return ParseResult::Ok();
	}
	else return valResult;

}

const ParseResult MultiBoolArg::ParseLongOperandAndSetDefined() {
	if (operands[0] != '=') 
		return ParseResult::Fail({ "In " + currentArg + ": Symbol '=' or space between option and operand was not found" });
	if (operands.size() <= 1) 
		return ParseResult::Fail({ "In " + currentArg + ": Symbol '='  was found, but there is no value" });

	operands = operands.substr(1);

	if (!isInteger(operands)) 
		return ParseResult::Fail({ "In " + currentArg + ": The option is found, but the value is not integer" });

	const auto num = atoi(operands.c_str());

	if (const auto valResult = validator.Check(num); valResult.IsOk()) {
		values.push_back(num == 1);

		isDefined = true;

		return ParseResult::Ok();
	}
	else return valResult;
}