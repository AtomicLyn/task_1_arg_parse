#include <catch2/catch_all.hpp>
#include <iostream>

#include "EmptyArg.hpp"

using namespace args_parse;

TEST_CASE("EmptyArg", "[all]")
{
	EmptyArg arg('c', "check");

	SECTION("Correct short and long name") {
		auto shortStr = "c";
		auto longStr = "check";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE(shortResult);
		REQUIRE(longResult);
	}

	SECTION("Wrong short and long name") {
		auto shortStr = "a";
		auto longStr = "aaaa";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}

	SECTION("Short and long name with operand") {
		auto shortStr = "c1";
		auto longStr = "check1";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE(shortResult);
		REQUIRE(longResult);
	}

	SECTION("Short and long name and eq character") {
		auto shortStr = "c=";
		auto longStr = "check=";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}

	SECTION("Short and long name and eq character with operand") {
		auto shortStr = "c=1";
		auto longStr = "check=1";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE(shortResult);
		REQUIRE(longResult);
	}	
}