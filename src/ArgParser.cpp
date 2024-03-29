#include "ArgParser.hpp"
#include "Arg.hpp"
#include <string>

using namespace args_parse;

void ArgParser::Add(Arg* argument) {
	arguments.push_back(argument);
}

const bool ArgParser::ParseSubsequence(const char* argumentWithoutDash) {
	const char* currentOption = argumentWithoutDash + 1;
	bool argumentDefined = false;

	for (; std::strlen(currentOption) != 0; currentOption++) {
		argumentDefined = false;

		for (auto argument : arguments) {

			if (argument->GetType() == ArgumentType::Empty) {

				if (argument->Parse(currentOption)) {
					argumentDefined = true;
					break;
				}
			}
		}
	}

	return argumentDefined;
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

		const std::string_view currentArgument(argument);
		bool argumentDefined = false;

		if (currentArgument.size() > 1) {

			if (currentArgument[0] == '-' && currentArgument[1] == '-' && currentArgument.size() > 2) {
				std::string_view argumentWithoutDash(&currentArgument[2]);

				for (auto j = 0; j < arguments.size(); j++) {

					if (arguments[j]->ParseLong(argumentWithoutDash.data())) {
						argumentDefined = true;
						break;
					}
				}
			}
			else if (currentArgument[0] == '-') {
				std::string_view argumentWithoutDash(&currentArgument[1]);

				for (auto argument : arguments) {

					if (argument->Parse(argumentWithoutDash.data())) {
						argumentDefined = true;

						if (argument->GetType() == ArgumentType::Empty && argumentWithoutDash.size() > 1) {
							argumentDefined = ParseSubsequence(argumentWithoutDash.data());
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
