#include "../dictionary/Dictionary.hpp"
#include "catch.hpp"
#include <string>
#include <vector>

const std::vector<std::string> INVALID_RUSSIAN_COLLOCATIONS{
	"",
	"42",
	"������111",
	"������!",
	"������-",
	"Hello",
};

const std::vector<std::string> VALID_RUSSIAN_COLLOCATIONS{
	"������",
	"������ ���",
	"���-�������",
	"������� �������",
};

const std::vector<std::string> INVALID_ENGLISH_COLLOCATIONS{
	"",
	"42",
	"Hello111",
	"Hello!",
	"Hello-",
	"������",
};

const std::vector<std::string> VALID_ENGLISH_COLLOCATIONS{
	"Hello",
	"Hello World",
	"kek-chebureck",
	"The Red Square",
};

SCENARIO("Basic functionality")
{
	GIVEN("A dictionary")
	{
		CDictionary dict;

		WHEN("Is created")
		{
			THEN("Does not have a sample word")
			{
				REQUIRE_FALSE(dict.Has("Cat"));
			}
			AND_WHEN("Sample word is added")
			{
				THEN("Sample word can be found")
				{
					dict.Add("Cat", "���");
					REQUIRE(dict.Has("Cat"));

					auto range = dict.Find("Cat");
					REQUIRE(std::distance(range.first, range.second) == 1);
					REQUIRE(range.first->first == "Cat");
					REQUIRE(range.first->second == "���");
				}
			}
		}

		THEN("Only valid English words or collocations can be added to it")
		{
			for (auto& word : VALID_ENGLISH_COLLOCATIONS)
			{
				CHECK_NOTHROW(dict.Add(word, "���"));
			}

			for (auto& word : INVALID_ENGLISH_COLLOCATIONS)
			{
				CHECK_THROWS(dict.Add(word, "���"));
			}
		}

		THEN("Only valid Russian words or collocations can be added to it")
		{
			for (auto& word : VALID_RUSSIAN_COLLOCATIONS)
			{
				CHECK_NOTHROW(dict.Add("abc", word));
			}

			for (auto& word : INVALID_RUSSIAN_COLLOCATIONS)
			{
				CHECK_THROWS(dict.Add("abc", word));
			}
		}
	}
}
