#include "ExpandTemplate.hpp"
#include "catch.hpp"

void CheckExpandTemplate(const std::string& tpl, const std::string& expectedResult, const Mapping& mapping)
{
	CHECK(ExpandTemplate(tpl, mapping) == expectedResult);
}

SCENARIO("Templates with 1 parameter")
{
	GIVEN("Simple template")
	{
		std::string tpl = "foobar";

		THEN("Parameter can be properly raplaced with a value")
		{
			CheckExpandTemplate(tpl, "barbar", {
				{"foo", "bar"},
			});
		}
		THEN("Parameter can be properly raplaced with a recurrent value")
		{
			CheckExpandTemplate(tpl, "barfoobar", {
				{ "foo", "barfoo" },
			});
		}
		THEN("Empty parameter name is ignored")
		{
			CheckExpandTemplate(tpl, "foobar", {
				{ "", "what?" },
			});
		}
	}

	GIVEN("Template with multiple choices to replace")
	{
		std::string tpl = "aaaaa";

		THEN("The leftmost variant is replaced")
		{
			CheckExpandTemplate(tpl, "!aa", {
				{ "aaa", "!" },
			});
		}
	}

	GIVEN("Template with parameter in multiple places")
	{
		std::string tpl = "{value} == {value}";

		THEN("Parameter can be properly raplaced with a value")
		{
			CheckExpandTemplate(tpl, "4 == 4", {
				{ "{value}", "4" },
			});
		}
	}

	GIVEN("Template with repeating parts")
	{
		std::string tpl = "12312312345";
	
		THEN("Parameter can be properly raplaced with a value")
		{
			CheckExpandTemplate(tpl, "123zzz5", {
				{ "1231234", "zzz" },
			});
		}
	}
}

SCENARIO("Templates with multiple parameters")
{
	GIVEN("Template with 2 parameters")
	{
		std::string tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";

		THEN("Parameter can be properly raplaced with a value")
		{
			CheckExpandTemplate(tpl, "Hello, Ivan Petrov. Today is Friday.", {
				{ "%USER_NAME%", "Ivan Petrov" },
				{ "{WEEK_DAY}", "Friday" },
			});
		}
		THEN("Values cannot be used as parameters after replacement")
		{
			CheckExpandTemplate(tpl, "Hello, {WEEK_DAY}. Today is Friday.", {
				{ "%USER_NAME%", "{WEEK_DAY}" },
				{ "{WEEK_DAY}", "Friday" },
			});
			CheckExpandTemplate(tpl, "Hello, Ivan Petrov. Today is %USER_NAME%.", {
				{ "%USER_NAME%", "Ivan Petrov" },
				{ "{WEEK_DAY}", "%USER_NAME%" },
			});
		}
		THEN("Leftmost parameter is prefered")
		{
			CheckExpandTemplate(tpl, "Hello, Ivan Petrov. Today is Friday.", {
				{ "USER", "Ivan" },
				{ "%USER_NAME%", "Ivan Petrov" },
				{ "{WEEK_DAY}", "Friday" },
			});
		}
		THEN("Parameter with longest name is prefered")
		{
			CheckExpandTemplate(tpl, "Hello, Ivan Petrov. Today is Friday.", {
				{ "%USER", "Ivan" },
				{ "%USER_NAME%", "Ivan Petrov" },
				{ "{WEEK_DAY}", "Friday" },
			});
		}
	}
}