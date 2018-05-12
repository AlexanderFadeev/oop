#include "FindMax.hpp"
#include "catch.hpp"


template <typename T, typename Less = std::less<T>>
void CheckFindMax(std::vector<T> vec, const T& expectedMax, const Less& less = std::less<T>())
{
	auto max = T();
	CHECK(FindMax(vec, max, less));
	CHECK(max == expectedMax);
}

template <typename T>
void CheckFindMaxFail(std::vector<T> vec)
{
	auto max = T();
	CHECK_FALSE(FindMax(vec, max));
	CHECK(max == T());
}


TEST_CASE("Empty vector")
{
	CheckFindMaxFail<int>({});
}

TEST_CASE("Various types")
{
	CheckFindMax<int>({ 1, 5, 2, 3, 4 }, 5);
	CheckFindMax<double>({ 3.141592, 2.71829, 0.5, 42.0 }, 42.0);
	CheckFindMax<char>({ 'a', 'd', 'e', 'q' }, 'q');
	CheckFindMax<std::string>({ "abc", "foo", "zebra" }, "zebra");
}

TEST_CASE("Custom predicate")
{
	CheckFindMax<int, std::greater<int>>({ 1, 5, 2, 3, 4 }, 1, std::greater<int>());
}