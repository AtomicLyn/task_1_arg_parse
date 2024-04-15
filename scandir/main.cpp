#include "ArgParser.hpp"
#include "Directory.hpp"
#include <iostream>

using namespace args_parse;

int main(int argc, const char** argv) {
	
	ArgParser parser;

	FileNameValidator<std::string> sourcePathValidator;
	SingleArg<std::string> sourcePath{ sourcePathValidator, 's', "source-path" };

	InRangeValidator<int> poolSizeValidator{ 0, 6 };
	SingleArg<int> poolSize{ poolSizeValidator, 'p', "pool-size"};

	SingleArg<UserChrono> debugSleep{ 'd', "debug-sleep" };

	parser.Add(&sourcePath);
	parser.Add(&poolSize);
	parser.Add(&debugSleep);

	if (auto result = parser.Parse(argc, argv); !result.IsOk())	std::cout << "Parse error: " << result.GetError().Message;
	if (!sourcePath.IsDefined()) std::cout << "source-path is not defined";
	else if (!poolSize.IsDefined()) std::cout << "pool-size is not defined";
	else if (!debugSleep.IsDefined()) std::cout << "debug-sleep is not defined";
	else {

		// TODO

	}
}