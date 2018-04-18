#include "Dictionary.hpp"
#include "catch.hpp"
#include <string>
#include <vector>

SCENARIO("Basic functionality")
{
	GIVEN("A dictionary")
	{
		SetCodePage(1251);
		CDictionary dict;

		WHEN("Is created")
		{
			THEN("Does not have a sample word")
			{
				REQUIRE_FALSE(dict.Has("Cat"));
			}
			AND_WHEN("Sample word is added")
			{
				dict.Add("Cat", "Кот");

				THEN("Sample word can be found")
				{
					REQUIRE(dict.Has("Cat"));

					auto range = dict.Find("Cat");
					REQUIRE(std::distance(range.first, range.second) == 1);
					REQUIRE(range.first->first == "Cat");
					REQUIRE(range.first->second == "Кот");
				}
			}
		}
	}
}

SCENARIO("Case insensitivity")
{
	GIVEN("A dictionary with sample word")
	{
		SetCodePage(1251);
		CDictionary dict;
		dict.Add("Cat", "Кот");

		THEN("It is case insensitive for English collocataions")
		{
			CHECK(dict.Has("Cat"));
			CHECK(dict.Has("cat"));
			CHECK(dict.Has("CAT"));
		}

		THEN("It is case insensitive for Russian collocataions")
		{
			CHECK(dict.Has("Кот"));
			CHECK(dict.Has("кот"));
			CHECK(dict.Has("КОТ"));
		}
	}
}

SCENARIO("Reverse translation")
{
	GIVEN("A dictionary")
	{
		SetCodePage(1251);
		CDictionary dict;

		WHEN("Words are added")
		{
			dict.Add("Cat", "Кот");

			THEN("Reversive translation can be performed")
			{
				REQUIRE(dict.Has("Кот"));
			}
		}

		WHEN("Words with the same translation are added")
		{
			dict.Add("Castle", "Замок");
			dict.Add("Lock", "Замок");

			THEN("Both words can be found")
			{
				auto range = dict.Find("Замок");

				REQUIRE(range.first->second == "Castle");
				REQUIRE(std::next(range.first)->second == "Lock");
			}
		}
	}
}
