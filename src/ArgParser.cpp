#include "ArgParser.hpp"
#include "Args.hpp"

using namespace args_parse;
using std::string;
using std::string_view;
using std::optional;
using std::pair;
using std::vector;
using std::shared_ptr;

void ArgParser::Add(Arg* argument) {
	arguments.push_back(argument);
}

ParseResult ArgParser::ParseSubsequence(string_view argumentWithoutDash, optional<string> nextArg, bool& usedNextArg) {
	string_view argumentWithoutOption(argumentWithoutDash.substr(1));
	bool argumentDefined = false;

	for (auto currentOption = argumentWithoutOption.begin(); currentOption != argumentWithoutOption.end(); currentOption++) {
		argumentDefined = false;

		for (const auto& argument : arguments) {

			/// Парсинг сокращенного названия аргумента
			if (const auto result = argument->ParseOption(&(*currentOption)); result.IsOk()) {
				argumentDefined = true;

				if (const auto operandResult = argument->ParseOperandAndSetDefined(nextArg, usedNextArg); operandResult.IsOk()) {

					/// Последний аргумент - не EmptyArg
					if (argument->GetType() != ArgumentType::Empty) return ParseResult::Ok();

					break;
				}
				else if (!operandResult.IsNotFound()) return operandResult;
			}
			else if (!result.IsNotFound()) return result;
		}

		if (!argumentDefined)
			return ParseResult::Fail({ "In " + string(argumentWithoutOption) + " : An argument was not found in the list of existing ones" });
	}

	return ParseResult::Ok();
}

ParseResult ArgParser::Parse(const int argc, const char** argv) {
	for (auto i = 1; i < argc; i++) {
		// Текущий аргумент
		const string currentArgument{ argv[i] };
		// Следующий аргумент, если таковой имеется
		optional<string> nextArgument;
		if (i < argc - 1) nextArgument = argv[i + 1];

		auto argumentDefined = false;
		auto usedNextArg = false;

		if (currentArgument.size() > 1) {

			/// Аргумент начинается с "--"
			if (currentArgument[0] == '-' && currentArgument[1] == '-' && currentArgument.size() > 2) {
				string_view argumentWithoutDash{ string_view{currentArgument}.substr(2) };

				/// Обработка частично встретившихся названий аргументов
				vector<pair<Arg*, int>> argMatches;

				for (const auto& argument : arguments) {

					/// Парсинг длинного названия
					if (const auto result = argument->ParseLongOption(argumentWithoutDash); result.first.IsOk()) {
						argMatches.emplace_back(argument, result.second);
					}
					else if (!result.first.IsNotFound()) return result.first;

				}

				/// Были найдены совпадения
				if (argMatches.size() > 0) {
					auto compFun = [](const pair<Arg*, int>& l, const pair<Arg*, int>& r) { return l.second < r.second; };

					/// Аргумент с максимальным совпадением символов
					auto maxMatch = std::max_element(argMatches.begin(), argMatches.end(), compFun);

					auto condFun = [&](const pair<Arg*, int>& el) { return el.second == maxMatch->second; };

					/// Количество аргументов с максимальным совпадением символов
					auto maxMatchCount = std::count_if(argMatches.begin(), argMatches.end(), condFun);

					/// Найдено несколько частичных совпадений одинаковой длины
					if (maxMatchCount > 1)
						return ParseResult::Fail({ "In " + string(currentArgument) + ": Several definitions of the argument have been found" });

					/// Парсинг единственного максимального аргумента
					if (const auto result = maxMatch->first->ParseLongOperandAndSetDefined(nextArgument, usedNextArg); result.IsOk()) argumentDefined = true;
					else if (!result.IsNotFound()) return result;
				}

			}
			/// Аргумент начинается с '-'
			else if (currentArgument[0] == '-') {
				string_view argumentWithoutDash{ string_view{currentArgument}.substr(1) };

				for (const auto& argument : arguments) {

					/// Парсинг сокращенного названия аргумента
					if (const auto result = argument->ParseOption(argumentWithoutDash); result.IsOk()) {

						if (const auto operandResult = argument->ParseOperandAndSetDefined(nextArgument, usedNextArg); operandResult.IsOk()) {
							argumentDefined = true;

							/// Аргумент является EmptyArg и строка еще имеет символы
							if (argument->GetType() == ArgumentType::Empty && argumentWithoutDash.size() > 1) {
								argumentDefined = false;

								/// Парсинг подпоследовательности в строке
								if (const auto subResult = ParseSubsequence(argumentWithoutDash, nextArgument, usedNextArg); subResult.IsOk()) {
									argumentDefined = true;
								}
								else if (!subResult.IsNotFound()) return subResult;

								break;
							}

							break;
						}
						else if (!operandResult.IsNotFound()) return operandResult;;

					}
					else if (!result.IsNotFound()) return result;
				}
			}
			else
				return ParseResult::Fail({ "In " + string(currentArgument) + " : The argument is set incorrectly - the character \'-\' is missing" });
		}

		if (!argumentDefined)
			return ParseResult::Fail({ "In " + string(currentArgument) + " : An argument was not found in the list of existing ones" });

		if (usedNextArg) i++;
	}

	return ParseResult::Ok();
}

const string ArgParser::GetHelp() const {
	string result = "";

	for (const auto& argument : arguments) {
		result += "-";
		result += argument->GetOption();
		result += " --";
		result += argument->GetLongOption();
		result += " | ";
		result += argument->GetDescription();
		result += "\n";
	}

	return result;
}
