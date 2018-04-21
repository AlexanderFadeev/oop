#include "String.hpp"
#include "catch.hpp"
#include <string>

void CheckString(const CString& string, const std::string expected)
{
	REQUIRE(string.GetLength() == expected.length());
	CHECK(std::string(string.GetData(), string.GetLength()) == expected);
}

const auto C_STR = "foo\0bar";
const size_t LEN = 7;
const std::string STL_STR(C_STR, LEN);

SCENARIO("Construction")
{
	SECTION("With default constructor")
	{
		CString str;
		CheckString(str, "");
	}

	SECTION("From c-string")
	{
		SECTION("Null-terminated")
		{
			CString str(C_STR);
			CheckString(str, C_STR);
		}
		SECTION("Certain size")
		{
			CString str(C_STR, LEN);
			CheckString(str, STL_STR);
		}
	}

	SECTION("From const CString")
	{
		const CString other(C_STR, LEN);
		CString str(other);
		CheckString(str, STL_STR);
	}

	SECTION("From rvalue CString")
	{
		CString other(C_STR, LEN);
		CString str(std::move(other));
		CheckString(str, STL_STR);
		CheckString(other, "");
	}

	SECTION("From std::string")
	{
		CString str(STL_STR);
		CheckString(str, STL_STR);
	}
}

SCENARIO("Operator =")
{
	SECTION("C-string")
	{
		CString str;
		str = C_STR;
		CheckString(str, C_STR);
	}

	SECTION("Const CString")
	{
		const CString other(C_STR, LEN);
		CString str;
		str = other;
		CheckString(str, STL_STR);
	}

	SECTION("Self")
	{
		CString str(STL_STR);
		str = str;
		CheckString(str, STL_STR);
	}

	SECTION("Rvalue CString")
	{
		CString other(C_STR, LEN);
		CString str;
		str = std::move(other);
		CheckString(str, STL_STR);
		CheckString(other, "");
	}

	SECTION("STL string")
	{
		CString str;
		str = STL_STR;
		CheckString(str, STL_STR);
	}
}

SCENARIO("Clearing")
{
	CString str(STL_STR);
	str.Clear();
	CheckString(str, "");
}

void CheckSubstring(const CString& str1, const std::string& str2, size_t start, size_t len = SIZE_MAX)
{
	CheckString(str1.SubString(start, len), str2.substr(start, len));
}

SCENARIO("Substring")
{
	CString str(STL_STR);

	SECTION("Full substring")
	{
		CheckSubstring(str, STL_STR, 0);
	}
	SECTION("Prefix of string")
	{
		CheckSubstring(str, STL_STR, 0, 5);
	}
	SECTION("Middle of string")
	{
		CheckSubstring(str, STL_STR, 3, 2);
	}
	SECTION("Exact suffix of string")
	{
		CheckSubstring(str, STL_STR, 4);
	}
	SECTION("Overflowed suffix of string")
	{
		CheckSubstring(str, STL_STR, 5, 42);
	}
}