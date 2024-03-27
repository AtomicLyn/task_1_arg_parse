#include "ArgParser.hpp"
#include "Arg.hpp"
#include <string>

using namespace args_parse;

std::vector<Arg*> ArgParser::variants;
std::vector<Arg*> ArgParser::arguments;

void ArgParser::Add(Arg* argument) {
	variants.push_back(argument);
}

bool ArgParser::TryParse(const int argc, const char** argv) {
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

		for (auto j = 0; j < variants.size(); j++) {

			if (*currentArgument.c_str() == '-' && *(currentArgument.c_str() + 1) == '-') {
				const char* argumentWithoutDash = currentArgument.c_str() + 2;

				if (variants[j]->TryParseLong(argumentWithoutDash)) {
					arguments.push_back(variants[j]);
					variants.erase(variants.begin() + j);

					argumentDefined = true;
				}
			}
			else if (*currentArgument.c_str() == '-') {
				const char* argumentWithoutDash = currentArgument.c_str() + 1;

				if (variants[j]->TryParse(argumentWithoutDash)) {
					arguments.push_back(variants[j]);
					variants.erase(variants.begin() + j);

					argumentDefined = true;
				}
			}

		}

		if (!argumentDefined) return false;
	}
	return true;
}

std::vector<Arg*> ArgParser::GetArguments() {
	return arguments;
}
