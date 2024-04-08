#include "MultiStringArg.hpp"

using namespace args_parse;

MultiStringArg::MultiStringArg(std::unique_ptr<StringValidator> validator, const char option, std::string longOption, std::string description)
	: validator{ std::move(validator) }, Arg(ArgumentType::MultiString, option, longOption, description) {};

const std::vector<std::string>& MultiStringArg::GetValues() const {
	return values;
}

const int MultiStringArg::GetCount() const {
	return values.size();
}

ParseResult MultiStringArg::ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;
	if (const auto valResult = validator->Check(operands); !valResult.IsOk()) return valResult;

	values.push_back(operands);
	isDefined = true;

	return ParseResult::Ok();
}

ParseResult MultiStringArg::ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;
	if (const auto valResult = validator->Check(operands); !valResult.IsOk()) return valResult;

	values.push_back(operands);
	isDefined = true;

	return ParseResult::Ok();
}

