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

TEST_CASE("BoolArg", "[all]")
{
	BoolArg arg('c', "check");

	SECTION("Correct short and long name with operand") {
		auto shortStr = "c1";
		auto longStr = "check1";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE(shortResult);
		REQUIRE(longResult);
	}

	SECTION("Wrong short and long name with operand") {
		auto shortStr = "a1";
		auto longStr = "aaaa1";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}

	SECTION("Short and long name with invalid operand") {
		auto shortStr = "c2";
		auto longStr = "check2";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
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

TEST_CASE("IntArg", "[all]")
{
	IntArg arg('c', "check");

	SECTION("Correct short and long name with operand") {
		auto shortStr = "c1";
		auto longStr = "check1";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE(shortResult);
		REQUIRE(longResult);
	}

	SECTION("Wrong short and long name with operand") {
		auto shortStr = "a1";
		auto longStr = "aaaa1";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}

	SECTION("Short and long name with invalid operand") {
		auto shortStr = "cfile.txt";
		auto longStr = "checkfile.txt";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
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

TEST_CASE("StringArg", "[all]")
{
	StringArg arg('c', "check");

	SECTION("Correct short and long name") {
		auto shortStr = "c";
		auto longStr = "check";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE(shortResult);
		REQUIRE(longResult);
	}

	SECTION("Wrong short and long name with operand") {
		auto shortStr = "a";
		auto longStr = "aaaa";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
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
		auto shortStr = "c=file.txt";
		auto longStr = "check=file.txt";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE(shortResult);
		REQUIRE(longResult);
	}
}

TEST_CASE("MultiBoolArg", "[all]")
{
	MultiBoolArg arg('c', "check");

	SECTION("Correct short and long name with operand") {
		auto shortStr = "c1";
		auto longStr = "check1";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE(shortResult);
		REQUIRE(longResult);
		REQUIRE(arg.GetCount() == 2);
	}

	SECTION("Wrong short and long name with operand") {
		auto shortStr = "a1";
		auto longStr = "aaaa1";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
		REQUIRE(arg.GetCount() == 0);
	}

	SECTION("Short and long name with invalid operand") {
		auto shortStr = "c2";
		auto longStr = "check2";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
		REQUIRE(arg.GetCount() == 0);
	}

	SECTION("Short and long name and eq character") {
		auto shortStr = "c=";
		auto longStr = "check=";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
		REQUIRE(arg.GetCount() == 0);
	}

	SECTION("Short and long name and eq character with operand") {
		auto shortStr = "c=1";
		auto longStr = "check=1";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE(shortResult);
		REQUIRE(longResult);
		REQUIRE(arg.GetCount() == 2);
	}
}

TEST_CASE("MultiIntArg", "[all]")
{
	MultiIntArg arg('c', "check");

	SECTION("Correct short and long name with operand") {
		auto shortStr = "c1";
		auto longStr = "check1";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE(shortResult);
		REQUIRE(longResult);
		REQUIRE(arg.GetCount() == 2);
	}

	SECTION("Wrong short and long name with operand") {
		auto shortStr = "a1";
		auto longStr = "aaaa1";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
	}

	SECTION("Short and long name with invalid operand") {
		auto shortStr = "cfile.txt";
		auto longStr = "checkfile.txt";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
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
		REQUIRE(arg.GetCount() == 2);
	}
}


TEST_CASE("MultiStringArg", "[all]")
{
	MultiStringArg arg('c', "check");

	SECTION("Correct short and long name") {
		auto shortStr = "c";
		auto longStr = "check";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE(shortResult);
		REQUIRE(longResult);
		REQUIRE(arg.GetCount() == 2);
	}

	SECTION("Wrong short and long name with operand") {
		auto shortStr = "a";
		auto longStr = "aaaa";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
		REQUIRE(arg.GetCount() == 0);
	}

	SECTION("Short and long name and eq character") {
		auto shortStr = "c=";
		auto longStr = "check=";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE_FALSE(shortResult);
		REQUIRE_FALSE(longResult);
		REQUIRE(arg.GetCount() == 0);
	}

	SECTION("Short and long name and eq character with operand") {
		auto shortStr = "c=file.txt";
		auto longStr = "check=file.txt";

		auto shortResult = arg.Parse(shortStr);
		auto longResult = arg.ParseLong(longStr);

		REQUIRE(shortResult);
		REQUIRE(longResult);
		REQUIRE(arg.GetCount() == 2);
	}
}