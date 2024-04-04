#include <catch2/catch_all.hpp>
#include <iostream>

#include "EmptyArg.hpp"
#include "BoolArg.hpp"
#include "IntArg.hpp"
#include "StringArg.hpp"
#include "MultiBoolArg.hpp"
#include "MultiIntArg.hpp"
#include "MultiStringArg.hpp"
#include "Validators.hpp"
#include "ArgParser.hpp"

using namespace args_parse;

TEST_CASE("IntValidator", "[basic]") {
	auto min = 0, max = 10;
	IntInRangeValidator rangeValidator{min, max};

	SECTION("Current value") {
		auto num = 5;

		auto result = rangeValidator.Check(num).IsOk();

		REQUIRE(result);
	}

	SECTION("Boundary values") {
		auto leftBound = min;
		auto rightBound = max;

		auto leftResult = rangeValidator.Check(leftBound).IsOk();
		auto rightResult = rangeValidator.Check(rightBound).IsOk();

		REQUIRE(leftResult);
		REQUIRE(rightResult);
	}

	SECTION("Unboundary values") {
		auto leftUnbound = min - 1;
		auto rightUnbound = max + 1;

		auto leftResult = rangeValidator.Check(leftUnbound).IsOk();
		auto rightResult = rangeValidator.Check(rightUnbound).IsOk();

		REQUIRE_FALSE(leftResult);
		REQUIRE_FALSE(rightResult);
	}
}

TEST_CASE("StringValidator", "[basic]") {
	StringFileNameValidator fileNameValidator;
	StringFileFormatValidator fileFormatValidator;

	SECTION("Current string filename") {
		auto str = "file-2.txt";

		auto result = fileNameValidator.Check(str).IsOk();

		REQUIRE(result);
	}

	SECTION("Wrong string filename ") {
		auto str = "file-2";

		auto result = fileNameValidator.Check(str).IsOk();

		REQUIRE_FALSE(result);
	}

	SECTION("Current string file format") {
		auto str = "*.txt";

		auto result = fileFormatValidator.Check(str).IsOk();

		REQUIRE(result);
	}

	SECTION("Wrong string file format") {
		auto str = ".txt";

		auto result = fileFormatValidator.Check(str).IsOk();

		REQUIRE_FALSE(result);
	}
}

TEST_CASE("Arg EmptyArg", "[basic]")
{
	EmptyArg arg{ 'c', "check" };

	SECTION("Correct short and long name") {
		auto shortStr = "c";
		auto longStr = "check";

		auto shortResult = arg.ParseOption(shortStr).IsOk();
		auto longResult = arg.ParseLongOption(longStr).first.IsOk();

		REQUIRE(shortResult);
		REQUIRE(longResult);
	}

	SECTION("Wrong short and long name") {
		auto shortStr = "a";
		auto longStr = "aaaa";

		auto shortResult = arg.ParseOption(shortStr).IsOk();
		auto longResult = arg.ParseLongOption(longStr).first.IsOk();

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}

	SECTION("Short and long name with operand") {
		auto shortStr = "c1";
		auto longStr = "check1";

		auto shortResult = arg.ParseOption(shortStr).IsOk();
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined().IsOk() : false;

		REQUIRE(shortResult);
		REQUIRE_FALSE(longResult);
	}

	SECTION("Short and long name and eq character") {
		auto shortStr = "c=";
		auto longStr = "check=";

		auto shortResult = arg.ParseOption(shortStr).IsOk();
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined().IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}

	SECTION("Short and long name and eq character with operand") {
		auto shortStr = "c=1";
		auto longStr = "check=1";

		auto shortResult = arg.ParseOption(shortStr).IsOk();
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined().IsOk() : false;

		REQUIRE(shortResult);
		REQUIRE(longResult);
	}
}

TEST_CASE("BoolArg", "[basic]") {
	BoolArg arg{ 'c', "check" };

	SECTION("Current argument with bool operand") {
		auto shortStr = "c1";
		auto longStr = "check=1";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined().IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined().IsOk() : false;

		REQUIRE(shortResult);
		REQUIRE(longResult);
	}

	SECTION("Wrong argument with not bool operand") {
		auto shortStr = "c9";
		auto longStr = "check=m";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined().IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined().IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}

	SECTION("Wrong argument with bool operand") {
		auto shortStr = "a1";
		auto longStr = "aaaaa=1";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined().IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined().IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}
}

TEST_CASE("IntArg", "[basic]") {
	IntArg arg{ new IntInRangeValidator{ 0, 10 }, 'c', "check" };

	SECTION("Current argument with int operand") {
		auto shortStr = "c=5";
		auto longStr = "check=5";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined().IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined().IsOk() : false;

		REQUIRE(shortResult);
		REQUIRE(longResult);
	}

	SECTION("Wrong argument with not int operand") {
		auto shortStr = "c=m";
		auto longStr = "check=m";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined().IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined().IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}


	SECTION("Wrong argument with int operand") {
		auto shortStr = "a=5";
		auto longStr = "aaaaa=5";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined().IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined().IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}
}

TEST_CASE("StringArg", "[basic]") {
	StringArg arg{ new StringFileNameValidator {}, 'c', "check" };

	SECTION("Current argument with string operand") {
		auto shortStr = "c=file.txt";
		auto longStr = "check=file.txt";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined().IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined().IsOk() : false;

		REQUIRE(shortResult);
		REQUIRE(longResult);
	}

	SECTION("Wrong argument with not string operand") {
		auto shortStr = "c=.txt";
		auto longStr = "check=.txt";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined().IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined().IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}


	SECTION("Wrong argument with string operand") {
		auto shortStr = "a=file.txt";
		auto longStr = "aaaaa=file.txt";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined().IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined().IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}
}

TEST_CASE("MultiBoolArg", "[basic]") {
	MultiBoolArg arg{ 'c', "check" };

	SECTION("Current argument with bool operand") {
		auto shortStr = "c1";
		auto longStr = "check=1";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined().IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined().IsOk() : false;

		REQUIRE(shortResult);
		REQUIRE(longResult);
		REQUIRE(arg.GetCount() == 2);
	}

	SECTION("Wrong argument with not bool operand") {
		auto shortStr = "c9";
		auto longStr = "check=m";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined().IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined().IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
		REQUIRE(arg.GetCount() == 0);
	}

	SECTION("Wrong argument with bool operand") {
		auto shortStr = "a1";
		auto longStr = "aaaaa=1";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined().IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined().IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
		REQUIRE(arg.GetCount() == 0);
	}
}

TEST_CASE("MultiIntArg", "[basic]") {
	MultiIntArg arg{ new IntInRangeValidator{ 0, 10 }, 'c', "check" };

	SECTION("Current argument with int operand") {
		auto shortStr = "c=5";
		auto longStr = "check=5";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined().IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined().IsOk() : false;

		REQUIRE(shortResult);
		REQUIRE(longResult);
		REQUIRE(arg.GetCount() == 2);
	}

	SECTION("Wrong argument with not int operand") {
		auto shortStr = "c=m";
		auto longStr = "check=m";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined().IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined().IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
		REQUIRE(arg.GetCount() == 0);
	}


	SECTION("Wrong argument with int operand") {
		auto shortStr = "a=5";
		auto longStr = "aaaaa=5";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined().IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined().IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
		REQUIRE(arg.GetCount() == 0);
	}
}

TEST_CASE("MultiStringArg", "[basic]") {
	MultiStringArg arg{ new StringFileNameValidator {}, 'c', "check" };

	SECTION("Current argument with int operand") {
		auto shortStr = "c=file.txt";
		auto longStr = "check=file.txt";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined().IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined().IsOk() : false;

		REQUIRE(shortResult);
		REQUIRE(longResult);
		REQUIRE(arg.GetCount() == 2);
	}

	SECTION("Wrong argument with not int operand") {
		auto shortStr = "c=.txt";
		auto longStr = "check=.txt";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined().IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined().IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
		REQUIRE(arg.GetCount() == 0);
	}


	SECTION("Wrong argument with int operand") {
		auto shortStr = "a=file.txt";
		auto longStr = "aaaaa=file.txt";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined().IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined().IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
		REQUIRE(arg.GetCount() == 0);
	}
}

TEST_CASE("ArgParser", "[basic]") {
	ArgParser parser;

	EmptyArg help{ 'h', "help", "Get some help" };
	EmptyArg sleep{ 's', "sleep" };
	BoolArg lock{ 'l', "lock", "Input 0 or 1 (ex. -l=0)" };

	IntArg warnings{ new IntInRangeValidator{0, 10}, 'w', "warnings"};
	IntArg warnas{ new IntInRangeValidator{0, 10}, 'w', "warnas" };

	StringArg name{ new StringFileNameValidator{}, 'n', "name" };
	MultiBoolArg authorizes{ 'a', "authorizes" };
	MultiIntArg codes{ new IntInRangeValidator{0, 10}, 'c', "codes" };
	MultiStringArg output{ new StringFileFormatValidator{}, 'o', "output" };
	
	parser.Add(&help);
	parser.Add(&sleep);
	parser.Add(&lock);
	parser.Add(&warnings);
	parser.Add(&warnas);
	parser.Add(&name);
	parser.Add(&output);
	parser.Add(&codes);
	parser.Add(&authorizes);

	SECTION("All current arguments") {
		std::vector args{"PLUG", "-hsl0",  "--warnings=10", "--warnas", "10", "-n", "file.txt", "-o=*.jpg",  "-c1", "--c=1", "-a=0"};

		auto result = parser.Parse(args.size(), &args[0]);

		REQUIRE(result.IsOk());
	}

	SECTION("Wrong argument") {
		std::vector args{ "PLUG", "-q" };

		auto result = parser.Parse(args.size(), &args[0]);

		REQUIRE_FALSE(result.IsOk());
	}

	SECTION("No arguments") {
		std::vector args{ "PLUG" };

		auto result = parser.Parse(args.size(), &args[0]);

		REQUIRE(result.IsOk());
	}

	SECTION("Current shortened arguments") {
		std::vector args{ "PLUG", "--warna=10", "--warni=10"};

		auto result = parser.Parse(args.size(), &args[0]);

		REQUIRE(result.IsOk());
	}

	SECTION("Duplicate shortened argument") {
		std::vector args{ "PLUG", "--warn=10" };

		auto result = parser.Parse(args.size(), &args[0]);

		REQUIRE_FALSE(result.IsOk());
	}
}