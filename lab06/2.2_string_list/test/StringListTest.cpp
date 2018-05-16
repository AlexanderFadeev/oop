#include "StringList.hpp"
#include "catch.hpp"
#include <algorithm>
#include <vector>

void CheckListIsEmpty(const StringList& list)
{
	CHECK(list.IsEmpty());
	CHECK(list.GetSize() == 0);
	CHECK(list.CBegin() == list.CEnd());
}

void CheckListSize(const StringList& list, size_t size)
{
	CHECK_FALSE(list.IsEmpty());
	CHECK(list.GetSize() == size);
	CHECK(std::distance(list.CBegin(), list.CEnd()) == static_cast<ptrdiff_t>(size));
}

void CheckListData(const StringList& list, const::std::vector<std::string> vec)
{
	CHECK(std::equal(list.CBegin(), list.CEnd(), vec.cbegin(), vec.cend()));
}

SCENARIO("Construction")
{
	GIVEN("A list")
	{
		StringList list;

		WHEN("It is created")
		{
			THEN("It is empty")
			{
				CheckListIsEmpty(list);
			}
		}
	}
}

SCENARIO("Pushing/popping values")
{
	GIVEN("A list")
	{
		StringList list;

		THEN("Items can be pushed into its front")
		{
			list.PushFront("foo");
			list.PushFront("bar");
			list.PushFront("baz");

			AND_THEN("Size is increased")
			{
				CheckListSize(list, 3);
			}
			AND_THEN("Items can be popped out of its front")
			{
				list.PopFront();
				list.PopFront();
				list.PopFront();

				AND_THEN("List is empty")
				{
					CheckListIsEmpty(list);
				}
			}
		}
		THEN("Item can be pushed into its back")
		{
			list.PushBack("foo");
			list.PushBack("bar");
			list.PushBack("baz");

			AND_THEN("Size is increased")
			{
				CheckListSize(list, 3);
			}
			AND_THEN("Item can be popped out of its front")
			{
				list.PopBack();
				list.PopBack();
				list.PopBack();

				AND_THEN("List is empty")
				{
					CheckListIsEmpty(list);
				}
			}
		}
	}
}

SCENARIO("Iteration")
{
	GIVEN("A list with data")
	{
		StringList list;
		std::vector<std::string> vec{ "foo", "bar", "baz" };

		THEN("It can be iterated")
		{
			std::copy(vec.begin(), vec.end(), std::back_inserter(list));

			AND_THEN("It can be const-iterated")
			{
				CHECK(std::equal(list.CBegin(), list.CEnd(), vec.cbegin(), vec.cend()));
			}
			AND_THEN("It can be const-reverse-iterated")
			{
				CHECK(std::equal(list.CRBegin(), list.CREnd(), vec.crbegin(), vec.crend()));
			}
			AND_THEN("It can be reverse-iterated")
			{
				size_t index = 0;
				std::for_each(list.RBegin(), list.REnd(), [&index](auto& value) {
					value = std::to_string(index++);
				});
				std::for_each(list.Begin(), list.End(), [&index](auto& value) {
					CHECK(value == std::to_string(--index));
				});
			}
			THEN("It can be iterated via range-based for")
			{
				size_t index = 0;
				for (auto& val : list)
				{
					CHECK(val == vec[index++]);
				}
			}
			GIVEN("A const list")
			{
				const auto constList = list;
				THEN("It can be iterated via range-based for")
				{
					size_t index = 0;
					for (auto& val : constList)
					{
						CHECK(val == vec[index++]);
					}
				}
			}
		}
	}
}

SCENARIO("Insertion")
{
	GIVEN("A list")
	{
		StringList list;

		THEN("Items can be inserted into empty list")
		{
			list.Insert(list.CBegin(), "bar");
			CheckListData(list, {"bar"});

			AND_THEN("Items can be inserted into list's beginning")
			{
				list.Insert(list.CBegin(), "foo");
				CheckListData(list, { "foo", "bar" });

				AND_THEN("Items can be inserted into list's middle")
				{
					list.Insert(++list.CBegin(), "baz");
					CheckListData(list, { "foo", "baz", "bar" });
				}
			}
			AND_THEN("Items can be inserted into list's ending")
			{
				list.Insert(list.CEnd(), "foo");
				CheckListData(list, { "bar", "foo" });
			}
		}
	}
}

SCENARIO("Erasure")
{
	GIVEN("A list with data")
	{
		StringList list;
		std::vector<std::string> vec{ "foo", "bar", "baz", "qux" };
		std::copy(vec.begin(), vec.end(), std::back_inserter(list));

		THEN("Items can be erased from list's middle")
		{
			list.Erase(++list.CBegin());
			CheckListData(list, { "foo", "baz", "qux" });

			AND_THEN("Items can be erased from list's beginning")
			{
				list.Erase(list.CBegin());
				CheckListData(list, { "baz", "qux" });

				AND_THEN("Items can be erased from list's ending")
				{
					list.Erase(--list.CEnd());
					CheckListData(list, { "baz" });

					AND_THEN("Items can be erased from list with single element")
					{
						list.Erase(list.CBegin());
						CheckListData(list, {});
					}
				}
			}
		}
	}
}