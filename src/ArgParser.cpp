#include "ArgParser.hpp"
#include "Arg.hpp"
#include <string>
#include <algorithm>

using namespace args_parse;

void ArgParser::Add(Arg* argument) {
	arguments.push_back(std::make_unique<Arg*>(argument));
}

const ParseResult ArgParser::ParseSubsequence(std::string_view argumentWithoutDash) {
	std::string_view argumentWithoutOption(&argumentWithoutDash[1]);
	bool argumentDefined = false;

	for (auto currentOption = argumentWithoutOption.begin(); currentOption != argumentWithoutOption.end(); currentOption++) {
		argumentDefined = false;

		for (const auto& argument : arguments) {

			if (const auto result = (*argument)->Parse(&(*currentOption)); result.IsOk()) {
				argumentDefined = true;

				/// Последний аргумент - не EmptyArg
				if ((*argument)->GetType() != ArgumentType::Empty) return ParseResult::Ok();
				break;
			}
			else if (!result.GetError().Message.empty()) return result;
		}

		if (!argumentDefined) return ParseResult::Fail();
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
				std::string_view argumentWithoutDash{ currentArgument.data() + 2 };

				/// Обработка частично встретившихся названий аргументов
				std::vector<std::pair<std::shared_ptr<Arg*>, int>> argMatches;

				for (const auto& argument : arguments) {
					if (const auto result = (*argument)->ParseLong(argumentWithoutDash); result.first.IsOk()) {
						argMatches.push_back(std::pair(argument, result.second));

						argumentDefined = true;
					}
					else if (!result.first.GetError().Message.empty()) return result.first;
				}

				/// Найдено несколько частичных совпадений
				if (argMatches.size() > 1) return ParseResult::Fail({ "In " + std::string(currentArgument) + ": Several definitions of the argument have been found" });
			}
			/// Аргумент начинается с '-'
			else if (currentArgument[0] == '-') {
				std::string_view argumentWithoutDash{ currentArgument.data() + 1 };

				for (const auto& argument : arguments) {

					if (const auto result = (*argument)->Parse(argumentWithoutDash); result.IsOk()) {
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
					else if (!result.GetError().Message.empty()) return result;
				}
			}
			else return ParseResult::Fail({ "In " + std::string(currentArgument) + ": The argument is set incorrectly: the character \'-\' is missing" });
		}

		if (!argumentDefined) return ParseResult::Fail({ "In " + std::string(currentArgument) + ": An argument with this value type was not found in the list of existing ones" });
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
