#include "ArgParser.hpp"
#include "Arg.hpp"
#include <string>

using namespace args_parse;

void ArgParser::Add(Arg* argument) {
	arguments.push_back(argument);
}

const bool ArgParser::ParseSubsequence(std::string_view argumentWithoutDash) {
	std::string_view argumentWithoutOption(&argumentWithoutDash[1]);
	bool argumentDefined = false;

	for (auto currentOption = argumentWithoutOption.begin(); currentOption != argumentWithoutOption.end(); currentOption++) {
		argumentDefined = false;

		for (const auto& argument : arguments) {

			if (argument->Parse(&(*currentOption))) {
				if (argument->GetType() != ArgumentType::Empty) return true;
				argumentDefined = true;
				break;
			}
		}

		if (!argumentDefined) return false;
	}

	return true;
}

bool ArgParser::Parse(const int argc, const char** argv) {
	for (auto i = 1; i < argc; i++) {
		std::string argument(argv[i]);

		if (i < argc - 1) {
			if (*argv[i + 1] != '-') {
				argument += argv[i + 1];
				i++;
			}
		}

		std::string_view currentArgument(argument);
		bool argumentDefined = false;

		if (currentArgument.size() > 1) {

			if (currentArgument[0] == '-' && currentArgument[1] == '-' && currentArgument.size() > 2) {
				std::string_view argumentWithoutDash(&currentArgument[2]);

				for (const auto& argument : arguments) {

					if (argument->ParseLong(argumentWithoutDash)) {
						argumentDefined = true;
						break;
					}
				}
			}
			else if (currentArgument[0] == '-') {
				std::string_view argumentWithoutDash(&currentArgument[1]);

				for (const auto& argument : arguments) {

					if (argument->Parse(argumentWithoutDash)) {
						argumentDefined = true;

						if (argument->GetType() == ArgumentType::Empty && argumentWithoutDash.size() > 1) {
							argumentDefined = ParseSubsequence(argumentWithoutDash);
						}

						break;
					}
				}
			}
		}

		if (!argumentDefined) return false;
	}
	return true;
}

const std::string ArgParser::GetHelp() const {
	std::string result = "";

	for (auto argument : arguments) {
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
