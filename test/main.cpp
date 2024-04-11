#include <catch2/catch_all.hpp>

#include "Args.hpp"
#include "Validators.hpp"
#include "ArgParser.hpp"
#include "UserTypes.hpp"

using namespace args_parse;

TEST_CASE("IntValidator", "[basic]") {
	auto min = 0, max = 10;
	InRangeValidator rangeValidator{ min, max };

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

TEST_CASE("FloatValidator", "[basic]") {
	auto min = 0.f, max = 10.f;
	InRangeValidator rangeValidator{ min, max };

	SECTION("Current value") {
		auto num = 5.f;

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
	FileNameValidator<std::string> fileNameValidator;
	FileFormatValidator fileFormatValidator;

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
	auto nextArg = std::nullopt;
	auto usedNextArg = false;

	SECTION("Correct short and long name") {
		auto shortStr = "c";
		auto longStr = "check";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE(shortResult);
		REQUIRE(longResult);
	}

	SECTION("Wrong short and long name") {
		auto shortStr = "a";
		auto longStr = "aaaa";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}

	SECTION("Short and long name with operand") {
		auto shortStr = "c1";
		auto longStr = "check1";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE(shortResult);
		REQUIRE_FALSE(longResult);
	}

	SECTION("Short and long name and eq character") {
		auto shortStr = "c=";
		auto longStr = "check=";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}

	SECTION("Short and long name and eq character with operand") {
		auto shortStr = "c=1";
		auto longStr = "check=1";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}
}

TEST_CASE("BoolArg", "[basic]") {
	SingleArg<bool> arg{ 'c', "check" };
	auto nextArg = std::nullopt;
	auto usedNextArg = false;

	SECTION("Current argument with bool operand") {
		auto shortStr = "c1";
		auto longStr = "check=1";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE(shortResult);
		REQUIRE(longResult);
	}

	SECTION("Wrong argument with not bool operand") {
		auto shortStr = "c9";
		auto longStr = "check=m";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}

	SECTION("Wrong argument with bool operand") {
		auto shortStr = "a1";
		auto longStr = "aaaaa=1";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}
}

TEST_CASE("IntArg", "[basic]") {
	SingleArg<int> arg{ std::make_unique<InRangeValidator<int>>(InRangeValidator<int>{ 0, 10 }), 'c', "check" };
	auto nextArg = std::nullopt;
	auto usedNextArg = false;

	SECTION("Current argument with int operand") {
		auto shortStr = "c=5";
		auto longStr = "check=5";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE(shortResult);
		REQUIRE(longResult);
	}

	SECTION("Wrong argument with not int operand") {
		auto shortStr = "c=m";
		auto longStr = "check=m";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}


	SECTION("Wrong argument with int operand") {
		auto shortStr = "a=5";
		auto longStr = "aaaaa=5";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}
}

TEST_CASE("FloatArg", "[basic]") {
	SingleArg<float> arg{ std::make_unique<InRangeValidator<float>>(InRangeValidator{ 0.f, 10.f }), 'c', "check" };
	auto nextArg = std::nullopt;
	auto usedNextArg = false;

	SECTION("Current argument with int operand") {
		auto shortStr = "c=5.5";
		auto longStr = "check=5.5";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE(shortResult);
		REQUIRE(longResult);
	}

	SECTION("Wrong argument with not int operand") {
		auto shortStr = "c=m";
		auto longStr = "check=m";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}


	SECTION("Wrong argument with int operand") {
		auto shortStr = "a=5.5";
		auto longStr = "aaaaa=5.5";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}
}

TEST_CASE("StringArg", "[basic]") {
	SingleArg<std::string> arg{ std::make_unique<FileNameValidator<std::string>>(FileNameValidator<std::string> {}), 'c', "check" };
	auto nextArg = std::nullopt;
	auto usedNextArg = false;

	SECTION("Current argument with string operand") {
		auto shortStr = "c=file.txt";
		auto longStr = "check=file.txt";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE(shortResult);
		REQUIRE(longResult);
	}

	SECTION("Wrong argument with not string operand") {
		auto shortStr = "c=.txt";
		auto longStr = "check=.txt";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}


	SECTION("Wrong argument with string operand") {
		auto shortStr = "a=file.txt";
		auto longStr = "aaaaa=file.txt";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}
}

TEST_CASE("MultiBoolArg", "[basic]") {
	MultiArg<bool> arg{ 'c', "check" };
	auto nextArg = std::nullopt;
	auto usedNextArg = false;

	SECTION("Current argument with bool operand") {
		auto shortStr = "c1";
		auto longStr = "check=1";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE(shortResult);
		REQUIRE(longResult);
		REQUIRE(arg.GetCount() == 2);
	}

	SECTION("Wrong argument with not bool operand") {
		auto shortStr = "c9";
		auto longStr = "check=m";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
		REQUIRE(arg.GetCount() == 0);
	}

	SECTION("Wrong argument with bool operand") {
		auto shortStr = "a1";
		auto longStr = "aaaaa=1";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
		REQUIRE(arg.GetCount() == 0);
	}
}

TEST_CASE("MultiIntArg", "[basic]") {
	MultiArg<int> arg{ std::make_unique<InRangeValidator<int>>(InRangeValidator<int>{ 0, 10 }), 'c', "check" };
	auto nextArg = std::nullopt;
	auto usedNextArg = false;

	SECTION("Current argument with int operand") {
		auto shortStr = "c=5";
		auto longStr = "check=5";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE(shortResult);
		REQUIRE(longResult);
		REQUIRE(arg.GetCount() == 2);
	}

	SECTION("Wrong argument with not int operand") {
		auto shortStr = "c=m";
		auto longStr = "check=m";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
		REQUIRE(arg.GetCount() == 0);
	}


	SECTION("Wrong argument with int operand") {
		auto shortStr = "a=5";
		auto longStr = "aaaaa=5";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
		REQUIRE(arg.GetCount() == 0);
	}
}

TEST_CASE("MultiFloatArg", "[basic]") {
	MultiArg<float> arg{ std::make_unique<InRangeValidator<float>>(InRangeValidator{ 0.f, 10.f }), 'c', "check" };
	auto nextArg = std::nullopt;
	auto usedNextArg = false;

	SECTION("Current argument with int operand") {
		auto shortStr = "c=5.5";
		auto longStr = "check=5.5";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE(shortResult);
		REQUIRE(longResult);
		REQUIRE(arg.GetCount() == 2);
	}

	SECTION("Wrong argument with not int operand") {
		auto shortStr = "c=m";
		auto longStr = "check=m";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
		REQUIRE(arg.GetCount() == 0);
	}


	SECTION("Wrong argument with int operand") {
		auto shortStr = "a=5.5";
		auto longStr = "aaaaa=5.5";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
		REQUIRE(arg.GetCount() == 0);
	}
}

TEST_CASE("MultiStringArg", "[basic]") {
	MultiArg<std::string> arg{ std::make_unique<FileNameValidator<std::string>>(FileNameValidator<std::string> {}), 'c', "check" };
	auto nextArg = std::nullopt;
	auto usedNextArg = false;

	SECTION("Current argument with int operand") {
		auto shortStr = "c=file.txt";
		auto longStr = "check=file.txt";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE(shortResult);
		REQUIRE(longResult);
		REQUIRE(arg.GetCount() == 2);
	}

	SECTION("Wrong argument with not int operand") {
		auto shortStr = "c=.txt";
		auto longStr = "check=.txt";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
		REQUIRE(arg.GetCount() == 0);
	}


	SECTION("Wrong argument with int operand") {
		auto shortStr = "a=file.txt";
		auto longStr = "aaaaa=file.txt";

		auto shortOptionResult = arg.ParseOption(shortStr).IsOk();
		auto shortResult = shortOptionResult ? arg.ParseOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;
		auto longOptionResult = arg.ParseLongOption(longStr).first.IsOk();
		auto longResult = longOptionResult ? arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg).IsOk() : false;

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
		REQUIRE(arg.GetCount() == 0);
	}
}

TEST_CASE("ArgParser", "[basic]") {
	ArgParser parser;

	EmptyArg help{ 'h', "help", "Get some help" };
	EmptyArg sleep{ 's', "sleep" };
	SingleArg<bool> lock{ 'l', "lock", "Input 0 or 1 (ex. -l=0)" };

	SingleArg<int> warnas{ std::make_unique<InRangeValidator<int>>(InRangeValidator{0, 10}), 'w', "warnas" };
	SingleArg<int> warnings{ std::make_unique<InRangeValidator<int>>(InRangeValidator{0, 10}), 'W', "warnings" };

	SingleArg<float> fraction{ std::make_unique<InRangeValidator<float>>(InRangeValidator{ 0.f,10.f }), 'F', "fraction"};
	SingleArg<std::string> name{ std::make_unique<FileNameValidator<std::string>>(FileNameValidator<std::string>{}), 'n', "name" };
	MultiArg<bool> authorizes{ 'a', "authorizes" };
	MultiArg<int> codes{ std::make_unique<InRangeValidator<int>>(InRangeValidator{0, 10}), 'c', "codes" };
	MultiArg<float> prices{ std::make_unique<InRangeValidator<float>>(InRangeValidator{0.f, 10000.f}), 'p', "prices" };
	MultiArg<std::string> output{ std::make_unique<FileFormatValidator<std::string>>(FileFormatValidator<std::string>{}), 'o', "output" };

	SingleArg<UserChrono> debugSleep{ 'd', "debug-sleep" };
	MultiArg<UserChrono> skipTimes{ 'S', "skip-times" };

	parser.Add(&help);
	parser.Add(&sleep);
	parser.Add(&lock);
	parser.Add(&warnas);
	parser.Add(&warnings);
	parser.Add(&fraction);
	parser.Add(&name);
	parser.Add(&authorizes);
	parser.Add(&codes);
	parser.Add(&prices);
	parser.Add(&output);
	parser.Add(&debugSleep);
	parser.Add(&skipTimes);

	SECTION("All current arguments") {
		std::vector args{ "PLUG", "-hsl0",  "--warnings=10", "--warnas", "10", "-n", "file.txt", "-o=*.jpg",  "-c1", "--c=1", "-a=0", "-F", "9.5", "-p=50.1", "-d=20s", "-S=3us"};

		auto result = parser.Parse(static_cast<int>(args.size()), &args[0]);

		REQUIRE(result.IsOk());
	}

	SECTION("Wrong argument") {
		std::vector args{ "PLUG", "-q" };

		auto result = parser.Parse(static_cast<int>(args.size()), &args[0]);

		REQUIRE_FALSE(result.IsOk());
	}

	SECTION("No arguments") {
		std::vector args{ "PLUG" };

		auto result = parser.Parse(static_cast<int>(args.size()), &args[0]);

		REQUIRE(result.IsOk());
	}

	SECTION("Current shortened arguments") {
		std::vector args{ "PLUG", "--warna=10", "--warni=10" };

		auto result = parser.Parse(static_cast<int>(args.size()), &args[0]);

		REQUIRE(result.IsOk());
	}

	SECTION("Duplicate shortened argument") {
		std::vector args{ "PLUG", "--warn=10" };

		auto result = parser.Parse(static_cast<int>(args.size()), &args[0]);

		REQUIRE_FALSE(result.IsOk());
	}

	SECTION("Wrong sequence short arguments") {
		std::vector args{ "PLUG", "-hsn=.txt" };

		auto result = parser.Parse(static_cast<int>(args.size()), &args[0]);

		REQUIRE_FALSE(result.IsOk());
	}
}
