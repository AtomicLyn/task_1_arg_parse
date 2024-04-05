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

const ParseResult MultiStringArg::ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;
	if (const auto valResult = (*validator)->Check(operands); !valResult.IsOk()) return valResult;

	values.push_back(operands);
	isDefined = true;

	return ParseResult::Ok();
}

const ParseResult MultiStringArg::ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;
	if (const auto valResult = (*validator)->Check(operands); !valResult.IsOk()) return valResult;

	values.push_back(operands);
	isDefined = true;

	return ParseResult::Ok();
}

