#pragma once

#include <vector>
#include "Arg.hpp"
#include <string>

namespace args_parse {
	class ArgParser {
	private:
		std::vector<Arg*> variants;
		std::vector<Arg*> arguments;
	public:
		void Add(Arg* argument);
		bool Parse(const int argc, const char** argv);
		std::string GetHelp();
		std::vector<Arg*> GetArguments();
	};
}
