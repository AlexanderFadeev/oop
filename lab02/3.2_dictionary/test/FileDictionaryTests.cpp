#include "FileDictionary.hpp"
#include "catch.hpp"
#include <filesystem>
#include <string>

namespace fs = std::experimental::filesystem;

const std::string TEST_FILE_NAME = "test.dat";

void DeleteTestFile()
{
	fs::remove(TEST_FILE_NAME);
}

SCENARIO("File handling")
{
	SetCodePage(1251);

	WHEN("File does not exist")
	{
		DeleteTestFile();

		THEN("File is created")
		{
			REQUIRE_FALSE(fs::exists(TEST_FILE_NAME));
			CFileDictionary dict(TEST_FILE_NAME);
			dict.Save();
			REQUIRE(fs::exists(TEST_FILE_NAME));
		}
	}

	GIVEN("An empty dictionary")
	{
		DeleteTestFile();
		CFileDictionary dict(TEST_FILE_NAME);

		WHEN("Words are added")
		{
			dict.Add("Cat", "Кот");
			dict.Add("Hi", "Привет");
			dict.Save();

			THEN("They are available after loading the file")
			{
				CFileDictionary otherDict(TEST_FILE_NAME);

				CHECK(otherDict.Has("Cat"));
				CHECK(otherDict.Has("Hi"));
				CHECK(otherDict.Has("Кот"));
				CHECK(otherDict.Has("Привет"));
			}
		}
	}
}
