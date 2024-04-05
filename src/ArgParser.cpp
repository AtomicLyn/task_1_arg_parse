#include "ArgParser.hpp"
#include "Arg.hpp"
#include <string>
#include <algorithm>

using namespace args_parse;

void ArgParser::Add(Arg* argument) {
	arguments.push_back(std::make_unique<Arg*>(argument));
}

const ParseResult ArgParser::ParseSubsequence(std::string_view argumentWithoutDash) {
	std::string_view argumentWithoutOption(argumentWithoutDash.substr(1));
	bool argumentDefined = false;

	for (auto currentOption = argumentWithoutOption.begin(); currentOption != argumentWithoutOption.end(); currentOption++) {
		argumentDefined = false;

		for (const auto& argument : arguments) {

			if (const auto result = (*argument)->ParseOption(&(*currentOption)); result.IsOk()) {
				argumentDefined = true;

				if (const auto operandResult = (*argument)->ParseOperandAndSetDefined(); operandResult.IsOk()) {

					/// Последний аргумент - не EmptyArg
					if ((*argument)->GetType() != ArgumentType::Empty) return ParseResult::Ok();

					break;
				}
				else if (!operandResult.GetError().Message.empty()) return operandResult;
			}
			else if (!result.GetError().Message.empty()) return result;
		}

		if (!argumentDefined) return ParseResult::Fail({"In " + std::string(argumentWithoutOption) + " : An argument was not found in the list of existing ones"});
	}

	return ParseResult::Ok();
}

const ParseResult ArgParser::Parse(const int argc, const char** argv) {
	for (auto i = 1; i < argc; i++) {
		std::string argument{ argv[i] };

		if (i < argc - 1) {
			/// Следующий элемент argv не содержит '-'
			if (*argv[i + 1] != '-') {
				argument += '=';
				argument += argv[i + 1];
				i++;
			}
		}

		std::string_view currentArgument{ argument }; ///< текущий аргумент с учетом склейки текущего и следующего
		bool argumentDefined = false;

		if (currentArgument.size() > 1) {

			/// Аргумент начинается с "--"
			if (currentArgument[0] == '-' && currentArgument[1] == '-' && currentArgument.size() > 2) {
				std::string_view argumentWithoutDash{ currentArgument.substr(2) };

				/// Обработка частично встретившихся названий аргументов
				std::vector<std::pair<std::shared_ptr<Arg*>, int>> argMatches;

				for (const auto& argument : arguments) {

					if (const auto result = (*argument)->ParseLongOption(argumentWithoutDash); result.first.IsOk()) {
						argMatches.push_back(std::pair(argument, result.second));
					}
					else if (!result.first.GetError().Message.empty()) return result.first;

				}

				if (argMatches.size() > 0) {
					auto compFun = [](const std::pair<std::shared_ptr<Arg*>, int>& l, const std::pair<std::shared_ptr<Arg*>, int>& r) { return l.second < r.second; };
					auto maxMatch = std::max_element(argMatches.begin(), argMatches.end(), compFun);

					auto condFun = [&](const std::pair<std::shared_ptr<Arg*>, int>& el) { return el.second == (*maxMatch).second; };
					auto maxMatchCount = std::count_if(argMatches.begin(), argMatches.end(), condFun);

					/// Найдено несколько частичных совпадений одинаковой длины
					if(maxMatchCount > 1) return ParseResult::Fail({ "In " + std::string(currentArgument) + ": Several definitions of the argument have been found" });

					if (const auto result = (*(*maxMatch).first)->ParseLongOperandAndSetDefined(); result.IsOk()) argumentDefined = true;
					else if (!result.GetError().Message.empty()) return result;
				}

			}
			/// Аргумент начинается с '-'
			else if (currentArgument[0] == '-') {
				std::string_view argumentWithoutDash{ currentArgument.substr(1)};

				for (const auto& argument : arguments) {

					if (const auto result = (*argument)->ParseOption(argumentWithoutDash); result.IsOk()) {

						if (const auto operandResult = (*argument)->ParseOperandAndSetDefined(); operandResult.IsOk()) {
							argumentDefined = true;

							/// Аргумент является EmptyArg и строка еще имеет символы
							if ((*argument)->GetType() == ArgumentType::Empty && argumentWithoutDash.size() > 1) {
								argumentDefined = false;

								if (const auto subResult = ParseSubsequence(argumentWithoutDash); subResult.IsOk()) {
									argumentDefined = true;
								}
								else if (!subResult.GetError().Message.empty()) return subResult;

								break;
							}

							break;
						}
						else if (!operandResult.GetError().Message.empty()) return operandResult;;

					}
					else if (!result.GetError().Message.empty()) return result;
				}
			}
			else return ParseResult::Fail({ "In " + std::string(currentArgument) + ": The argument is set incorrectly: the character \'-\' is missing" });
		}

		if (!argumentDefined) return ParseResult::Fail({ "In " + std::string(currentArgument) + ": An argument was not found in the list of existing ones" });
	}

	return ParseResult::Ok();
}

const std::string ArgParser::GetHelp() const {
	std::string result = "";

	for (const auto& argument : arguments) {
		result += "-";
		result += (*argument)->GetOption();
		result += " --";
		result += (*argument)->GetLongOption();
		result += " | ";
		result += (*argument)->GetDescription();
		result += "\n";
	}

	return result;
}
