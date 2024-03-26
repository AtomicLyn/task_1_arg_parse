#include "ArgParser.hpp"
#include "Arg.hpp"

using namespace args_parse;

std::vector<Arg*> ArgParser::variants;
std::vector<Arg*> ArgParser::arguments;

void ArgParser::Add(Arg* argument) {
	variants.push_back(argument);
}

bool ArgParser::TryParse(const int argc, const char** argv) {
	for (auto i = 1; i < argc; i++) {
		bool argumentDefined = false;
		for (auto argument : variants) {
			if (argument->TryParse(argv[i])) {
				arguments.push_back(argument);
				argumentDefined = true;
			}
		}
		if (!argumentDefined) return false;
	}
	return true;
}

std::vector<Arg*> ArgParser::GetArguments() {
	return arguments;
}
