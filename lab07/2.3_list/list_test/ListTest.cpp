#include "List.hpp"
#include "catch.hpp"
#include <functional>
#include <string>

using namespace std::string_literals;

template <typename T>
void CheckInstantation(T value)
{
	GIVEN("A list of type CList<T>")
	{
		CList<T> list;

		THEN("Values of type T can be pushed into it")
		{
			list.PushBack(value);
			list.PushFront(value);
		}
	}
}

struct SCustomType {};

SCENARIO("Instantation for various types")
{
	CheckInstantation(42);
	CheckInstantation('Z');
	CheckInstantation("ABC"s);
	CheckInstantation(SCustomType());

	auto fn = std::function<bool(int, int)>(std::less<int>());
	CheckInstantation(fn);
}

struct MockThrowTag{};

struct Mock
{
	Mock(int data)
		: data(data)
	{
	}

	Mock(const Mock& other)
		: data(other.data + 1)
	{
		if (other.data == 42)
		{
			throw MockThrowTag{};
		}
	}

	int data;
};

SCENARIO("Exception safety")
{
	GIVEN("A list of mock objects")
	{
		CList<Mock> mockList;
		mockList.PushBack(1);
		mockList.PushBack(41);
		mockList.PushBack(3);

		THEN("Exception is thrown when it is tried to be copied via constructor")
		{
			CHECK_THROWS_AS(CList<Mock>(mockList), MockThrowTag);
		}

		THEN("Exception is thrown when it is tried to be copied via assignment")
		{
			CList<Mock> other;
			CHECK_THROWS_AS(other = mockList, MockThrowTag);

			AND_THEN("Other list is not modified")
			{
				CHECK(other.IsEmpty());
				CHECK(other.GetSize() == 0);
				CHECK(other.cbegin() == other.cend());
			}
		}
	}
}