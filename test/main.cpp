#include <catch2/catch_all.hpp>
#include <iostream>

#include "EmptyArg.hpp"
#include "BoolArg.hpp"
#include "IntArg.hpp"
#include "StringArg.hpp"
#include "MultiBoolArg.hpp"
#include "MultiIntArg.hpp"
#include "MultiStringArg.hpp"

using namespace args_parse;

TEST_CASE("Arg EmptyArg", "[basic]")
{
	EmptyArg arg('c', "check");

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
		auto longResult = arg.ParseLongOption(longStr).first.IsOk();

		REQUIRE(shortResult);
		REQUIRE(longResult);
	}

	SECTION("Short and long name and eq character") {
		auto shortStr = "c=";
		auto longStr = "check=";

		auto shortResult = arg.ParseOption(shortStr).IsOk();
		auto longResult = arg.ParseLongOption(longStr).first.IsOk();

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}

	SECTION("Short and long name and eq character with operand") {
		auto shortStr = "c=1";
		auto longStr = "check=1";

		auto shortResult = arg.ParseOption(shortStr).IsOk();
		auto longResult = arg.ParseLongOption(longStr).first.IsOk();

		REQUIRE(shortResult);
		REQUIRE(longResult);
	}	
}