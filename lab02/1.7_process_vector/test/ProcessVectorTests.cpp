#include "../process_vector/ProcessVector.hpp"
#include "catch.hpp"

TEST_CASE("Throws when not enough elements provided", "[processVector]")
{
	std::vector<double> emptyVec;
	CHECK_THROWS(ProcessVector(emptyVec));

	std::vector<double> smallVec(LEAST_ELEMENTS_COUNT - 1);
	CHECK_THROWS(ProcessVector(smallVec));
}

TEST_CASE("Does not change the vector when least elements are zero", "[processVector]")
{
	std::vector<double> origVec(LEAST_ELEMENTS_COUNT);
	origVec.push_back(42);

	auto vec = origVec;
	ProcessVector(vec);
	CHECK(vec == origVec);
}

TEST_CASE("Works for sample vector", "[processVector]")
{
	std::vector<double> vec{ 1, 2, 3, 4, 5 };
	std::vector<double> expected{ 7, 8, 9, 10, 11 };
	ProcessVector(vec);
	CHECK(vec == expected);
}

TEST_CASE("Works for another sample vector", "[processVector]")
{
	std::vector<double> vec{ -1, 0, 1, 42, 1337 };
	std::vector<double> expected = vec;
	ProcessVector(vec);
	CHECK(vec == expected);
}
