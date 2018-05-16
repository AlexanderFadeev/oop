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