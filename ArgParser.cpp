#include "ArgParser.hpp"
#include "Arg.hpp"
#include <string>

using namespace args_parse;

void ArgParser::Add(Arg* argument) {
	variants.push_back(argument);
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

		const std::string currentArgument(argument);

		bool argumentDefined = false;

		if (*currentArgument.c_str() == '-' && *(currentArgument.c_str() + 1) == '-') {
			const char* argumentWithoutDash = currentArgument.c_str() + 2;

			for (auto j = 0; j < variants.size(); j++) {

				if (variants[j]->ParseLong(argumentWithoutDash)) {
					argumentDefined = true;
					break;
				}
			}
		}
		else if (*currentArgument.c_str() == '-') {
			const char* argumentWithoutDash = currentArgument.c_str() + 1;

			for (auto j = 0; j < variants.size(); j++) {

				if (variants[j]->Parse(argumentWithoutDash)) {
					argumentDefined = true;

					if (variants[j]->GetType() == ArgumentType::Empty && std::strlen(argumentWithoutDash) > 1) {
						const char* currentOption = argumentWithoutDash + 1;

						for (; std::strlen(currentOption) != 0; currentOption++) {
							argumentDefined = false;

							for (auto k = 0; k < variants.size(); k++) {

								if (variants[k]->GetType() == ArgumentType::Empty) {
									
									if (variants[k]->Parse(currentOption)) {
										argumentDefined = true;
										break;
									}
								}
							}
						}
					}

					break;
				}
			}
		}

		if (!argumentDefined) return false;
	}
	return true;
}

std::string ArgParser::GetHelp() {
	std::string result = "";

	for (auto variant : variants) {
		result += "-";
		result += variant->GetOption();
		result += " --";
		result += variant->GetLongOption();
		result += " | ";
		result += variant->GetDescription();
		result += "\n";
	}

	return result;
}

std::vector<Arg*> ArgParser::GetArguments() {
	return arguments;
}
