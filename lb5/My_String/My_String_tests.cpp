#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "CMyString.h"

TEST_CASE("String create")
{
	SECTION("Default construct")
	{
		CMyString str;
		CHECK(str.GetLength() == 0);
		CHECK(str.GetCapacity() == 0);
		CHECK(strcmp(str.GetStringData(), "") == 0);
	}

	SECTION("Construct with char*") 
	{
		CMyString str("Hello");
		CHECK(str.GetLength() == 5);
		CHECK(str.GetCapacity() >= 5);
		CHECK(strcmp(str.GetStringData(), "Hello") == 0);
	}

	SECTION("Construct with null character in middle") 
	{
		CMyString str("Hello\0World", 11);
		CHECK(str.GetLength() == 11);
		CHECK(str.GetCapacity() >= 11);
		CHECK(memcmp(str.GetStringData(), "Hello\0World", 11) == 0);
	}

	SECTION("Construct with std::string") 
	{
		std::string s = "Test";
		CMyString str(s);
		CHECK(str.GetLength() == 4);
		CHECK(strcmp(str.GetStringData(), "Test") == 0);
	}
}

TEST_CASE("String operations") 
{
	SECTION("Concatenation (+=)") 
	{
		CMyString str("Hello");
		str += " World";
		CHECK(str.GetLength() == 11);
		CHECK(strcmp(str.GetStringData(), "Hello World") == 0);
	}

	SECTION("Concatenation (+)") 
	{
		CMyString a("Hello");
		CMyString b(" World");
		CMyString c = a + b;
		CHECK(c.GetLength() == 11);
		CHECK(strcmp(c.GetStringData(), "Hello World") == 0);
	}

	SECTION("Mixed concatenation") 
	{
		CMyString a("A");
		std::string b = "B";
		const char* c = "C";

		CMyString res1 = a + b;
		CMyString res2 = b + a;
		CMyString res3 = a + c;
		CMyString res4 = c + a;

		CHECK(res1 == "AB");
		CHECK(res2 == "BA");
		CHECK(res3 == "AC");
		CHECK(res4 == "CA");
	}
}

TEST_CASE("String comparison") 
{
	SECTION("Equality") 
	{
		CMyString a("Test");
		CMyString b("Test");
		CMyString c("Different");

		CHECK(a == b);
		CHECK_FALSE(a == c);
	}

	SECTION("Inequality") 
	{
		CMyString a("A");
		CMyString b("B");

		CHECK(a != b);
		CHECK(a < b);
		CHECK(b > a);
	}
}

TEST_CASE("String access") 
{
	CMyString str("Hello");

	SECTION("Valid index") 
	{
		CHECK(str[0] == 'H');
		CHECK(str[4] == 'o');
	}

	SECTION("Invalid index") 
	{
		CHECK_THROWS_AS(str[5], std::out_of_range);
		CHECK_THROWS_AS(str[-1], std::out_of_range);
	}

	SECTION("Modification") 
	{
		str[1] = 'a';
		CHECK(strcmp(str.GetStringData(), "Hallo") == 0);
	}
}

TEST_CASE("String functions") 
{
	SECTION("Substring") 
	{
		CMyString str("Hello World");

		SECTION("Valid substring") 
		{
			CMyString sub = str.SubString(6);
			CHECK(sub == "World");
		}

		SECTION("Partial substring") 
		{
			CMyString sub = str.SubString(6, 2);
			CHECK(sub == "Wo");
		}

		SECTION("Invalid start position") 
		{
			CHECK(str.SubString(100).GetLength() == 0);
		}
	}

	SECTION("Clear") 
	{
		CMyString str("Text");
		str.Clear();
		CHECK(str.GetLength() == 0);
		CHECK(str.GetCapacity() == 0);
		CHECK(strcmp(str.GetStringData(), "") == 0);
	}
}

TEST_CASE("Edge cases") 
{
	SECTION("Empty string operations") 
	{
		CMyString empty;
		CMyString a("A");

		CHECK((empty + a) == "A");
		CHECK((a + empty) == "A");
		CHECK((empty + empty) == "");
	}

	SECTION("Self-assignment") 
	{
		CMyString str("Test");
		str = str;
		CHECK(str == "Test");
	}

	SECTION("Move semantics") 
	{
		CMyString a("Hello");
		CMyString b(std::move(a));

		CHECK(b == "Hello");
		CHECK(a.GetLength() == 0);
		CHECK(a.GetCapacity() == 0);
	}
}

TEST_CASE("IO operations") 
{
	SECTION("Output") 
	{
		CMyString str("Test output");
		std::ostringstream oss;
		oss << str;
		CHECK(oss.str() == "Test output");
	}

	SECTION("Input") 
	{
		CMyString str;
		std::istringstream iss("Test input");
		iss >> str;
		CHECK(str == "Test input");
	}
}