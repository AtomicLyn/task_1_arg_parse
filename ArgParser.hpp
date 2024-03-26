#pragma once

#include <vector>
#include "Arg.hpp"

namespace args_parse {
	class ArgParser {
	private:
		static std::vector<Arg*> variants;
		static std::vector<Arg*> arguments;
	public:
		void Add(Arg* argument);
		bool TryParse(const int argc, const char** argv);
		std::vector<Arg*> GetArguments();
	};
}
