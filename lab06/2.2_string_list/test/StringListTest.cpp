#include "StringList.hpp"
#include "catch.hpp"
#include <algorithm>
#include <vector>

using StringVector = std::vector<std::string>;

void CheckListIsEmpty(const StringList& list)
{
	CHECK(list.IsEmpty());
	CHECK(list.GetSize() == 0);
	CHECK(list.cbegin() == list.cend());
}

void CheckListSize(const StringList& list, size_t size)
{
	CHECK_FALSE(list.IsEmpty());
	CHECK(list.GetSize() == size);
	CHECK(std::distance(list.cbegin(), list.cend()) == static_cast<ptrdiff_t>(size));
}

void CheckListData(const StringList& list, const StringVector& vec)
{
	CHECK(std::equal(list.cbegin(), list.cend(), vec.cbegin(), vec.cend()));
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
		THEN("Items can be pushed into its back")
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

SCENARIO("Copy/Move Construction/Assignment")
{
	GIVEN("A list with data")
	{
		StringList list;
		StringVector vec{ "foo", "bar", "baz" };
		std::copy(vec.begin(), vec.end(), std::back_inserter(list));

		THEN("Other list can be copy-constructed from it")
		{
			StringList other(list);
			CheckListData(other, vec);
		}
		THEN("It can be copied to another list")
		{
			StringList other;
			other = list;
			CheckListData(other, vec);
		}
		THEN("Other list can be move-constructed from it")
		{
			StringList other(std::move(list));
			CheckListData(other, vec);
			CheckListData(list, {});
		}
		THEN("It can be copied to another list")
		{
			StringList other;
			other = std::move(list);
			CheckListData(other, vec);
			CheckListData(list, {});
		}
		THEN("It can be safely self-copied")
		{
			list = list;
			CheckListData(list, vec);
		}
		THEN("It can be safely self-moved")
		{
			list = std::move(list);
			CheckListData(list, vec);
		}
	}
}

SCENARIO("Iteration")
{
	GIVEN("A string list iterator")
	{
		StringList list;
		list.PushBack("foo");
		list.PushBack("bar");
		list.PushBack("baz");
		auto it = list.begin();

		THEN("It can be derefernced")
		{
			CHECK(*it == "foo");
		}
		THEN("It can be derefernced via ->")
		{
			CHECK(it->size() == 3);
		}
		THEN("It can incremented and decremented")
		{
			CHECK(*(it++) == "foo");
			CHECK(*it == "bar");
			CHECK(*(it--) == "bar");
			CHECK(*it == "foo");
			CHECK(*(++it) == "bar");
			CHECK(*(--it) == "foo");
		}
		THEN("It can compared")
		{
			auto next = std::next(it);

			CHECK(it == it);
			CHECK_FALSE(it != it);

			CHECK_FALSE(it == next);
			CHECK_FALSE(next == it);
			CHECK(it != next);
			CHECK(next != it);
		}
	}
	GIVEN("A list with data")
	{
		StringList list;
		StringVector vec{ "foo", "bar", "baz" };

		THEN("It can be iterated")
		{
			std::copy(vec.begin(), vec.end(), std::back_inserter(list));

			AND_THEN("It can be const-iterated")
			{
				CHECK(std::equal(list.cbegin(), list.cend(), vec.cbegin(), vec.cend()));
			}
			AND_THEN("It can be const-reverse-iterated")
			{
				CHECK(std::equal(list.crbegin(), list.crend(), vec.crbegin(), vec.crend()));
			}
			AND_THEN("It can be reverse-iterated")
			{
				size_t index = 0;
				std::for_each(list.rbegin(), list.rend(), [&index](auto& value) {
					value = std::to_string(index++);
				});
				std::for_each(list.begin(), list.end(), [&index](auto& value) {
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
			list.Insert(list.cbegin(), "bar");
			CheckListData(list, {"bar"});

			AND_THEN("Items can be inserted into list's beginning")
			{
				list.Insert(list.cbegin(), "foo");
				CheckListData(list, { "foo", "bar" });

				AND_THEN("Items can be inserted into list's middle")
				{
					list.Insert(++list.cbegin(), "baz");
					CheckListData(list, { "foo", "baz", "bar" });
				}
			}
			AND_THEN("Items can be inserted into list's ending")
			{
				list.Insert(list.cend(), "foo");
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
		StringVector vec{ "foo", "bar", "baz", "qux" };
		std::copy(vec.begin(), vec.end(), std::back_inserter(list));

		THEN("Items can be erased from list's middle")
		{
			list.Erase(++list.cbegin());
			CheckListData(list, { "foo", "baz", "qux" });

			AND_THEN("Items can be erased from list's beginning")
			{
				list.Erase(list.cbegin());
				CheckListData(list, { "baz", "qux" });

				AND_THEN("Items can be erased from list's ending")
				{
					list.Erase(--list.cend());
					CheckListData(list, { "baz" });

					AND_THEN("Items can be erased from list with single element")
					{
						list.Erase(list.cbegin());
						CheckListData(list, {});
					}
				}
			}
		}
	}
}
