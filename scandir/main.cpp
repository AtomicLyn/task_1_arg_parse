#include "ArgParser.hpp"
#include "Directory.hpp"
#include <iostream>
#include "ScanPool.hpp"

using namespace args_parse;
using namespace scan_dir;

int main(int argc, const char** argv) {
	
	ArgParser parser;

	EmptyArg help{ 'h', "help" };
	SingleArg<std::string> sourcePath{ 's', "source-path", "The path for the directory where the multithreaded crawl will be performed (ex. -s=C:\\folder)"};
	InRangeValidator<int> poolSizeValidator{ 1, 8 };
	SingleArg<int> poolSize{ poolSizeValidator, 'p', "pool-size", "Thread pool size for multithreaded traversal (ex. -p=4)"};
	SingleArg<UserChrono> debugSleep{ 'd', "debug-sleep", "Time in <chrono_literals> to freeze the first thread (ex. -d=100ms)"};

	parser.Add(&help);
	parser.Add(&sourcePath);
	parser.Add(&poolSize);
	parser.Add(&debugSleep);

	if (auto result = parser.Parse(argc, argv); !result.IsOk())	std::cout << "Parse error: " << result.GetError().Message;
	if (help.IsDefined()) std::cout << parser.GetHelp() << std::endl;

	if (!sourcePath.IsDefined()) std::cout << "source-path is not defined";
	else if (!poolSize.IsDefined()) std::cout << "pool-size is not defined";
	else if (!debugSleep.IsDefined()) std::cout << "debug-sleep is not defined";
	else {
		ScanPool pool{ sourcePath.GetValue(), poolSize.GetValue(), debugSleep.GetValue().GetMicroseconds() };

		auto mainDirectory = pool.StartAndGetDirectory();

		std::cout << "Read: " << mainDirectory.GetPath() << std::endl << std::endl;

		mainDirectory.Show();
	}

	return 0;
}