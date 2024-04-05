#include "MultiStringArg.hpp"

using namespace args_parse;

MultiStringArg::MultiStringArg(StringValidator* validator, const char option, std::string longOption, std::string description)
	: validator{ std::make_unique<StringValidator*>(std::move(validator)) }, Arg(ArgumentType::MultiString, option, longOption, description) {};

const std::vector<std::string> MultiStringArg::GetValues() {
	return values;
}

const int MultiStringArg::GetCount() {
	return values.size();
}

const ParseResult MultiStringArg::ParseOperandAndSetDefined() {
	if (const auto valResult = (*validator)->Check(operands); valResult.IsOk()) {
		values.push_back(operands);

		isDefined = true;

		return ParseResult::Ok();
	}
	else return valResult;
}

const ParseResult MultiStringArg::ParseLongOperandAndSetDefined() {
	if (operands[0] != '=') 
		return ParseResult::Fail({ "In " + currentArg + ": Symbol '=' or space between option and operand was not found" });
	if (operands.size() <= 1) 
		return ParseResult::Fail({ "In " + currentArg + ": Symbol '='  was found, but there is no value" });

	operands = operands.substr(1);

	if (const auto valResult = (*validator)->Check(operands); valResult.IsOk()) {
		values.push_back(operands);

		isDefined = true;

		return ParseResult::Ok();
	}
	else return valResult;
}

