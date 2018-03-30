#include "Calculator.hpp"
#include "catch.hpp"
#include <array>
#include <sstream>

const std::array<std::string, 5> INVALID_IDENTIFIERS{
	"",
	"42",
	"0_fOO",
	"foo-BAR",
	"foo_bar!",
};

const std::array<std::string, 4> VALID_IDENTIFIERS{
	"FooBarBaz",
	"foo_BAR_baz",
	"foo_42",
	"_F00_bar_",
};

SCENARIO("Calculator variables")
{
	GIVEN("A calculator")
	{
		CCalculator calc;

		THEN("Only valid identifiers can be used for variable names")
		{
			for (auto& i : VALID_IDENTIFIERS)
			{
				CHECK_NOTHROW(calc.Var(i));
			}

			for (auto& i : INVALID_IDENTIFIERS)
			{
				CHECK_THROWS(calc.Var(i));
			}
		}

		THEN("Variables can be created via `Let`")
		{
			for (auto& i : VALID_IDENTIFIERS)
			{
				CHECK_NOTHROW(calc.Var(i));
			}
		}

		WHEN("Identifier is defined")
		{
			const std::string id("foo");
			calc.Var(id);

			THEN("It's NaN")
			{
				REQUIRE(std::isnan(calc.GetValue(id)));
			}
			THEN("It can't be redefined")
			{
				REQUIRE_THROWS(calc.Var(id));
			}
			THEN("It can have value assigned to it")
			{
				calc.Let(id, 42);
				REQUIRE(calc.GetValue(id) == 42);
			}
			THEN("It can't have value of undefined variable assigned to it")
			{
				REQUIRE_THROWS(calc.Let(id, "god"));
			}
			THEN("It can have value of other variable assigned to it")
			{
				const std::string otherID("bar");
				calc.Var(otherID);
				calc.Let(otherID, 42);
				calc.Let(id, otherID);
				REQUIRE(calc.GetValue(id) == 42);

				AND_THEN("It does not change with other variable")
				{
					calc.Let(otherID, 420);
					REQUIRE(calc.GetValue(id) == 42);
				}
			}
		}
	}
}

using Operator = CFunction::Operator;

SCENARIO("Calculator functions")
{
	GIVEN("A calculator")
	{
		CCalculator calc;

		THEN("Only valid identifiers can be used for function names")
		{
			const std::string id("foo");
			calc.Var(id);

			for (auto& i : VALID_IDENTIFIERS)
			{
				CHECK_NOTHROW(calc.Func(i, id));
			}

			for (auto& i : INVALID_IDENTIFIERS)
			{
				CHECK_THROWS(calc.Func(i, id));
			}
		}

		WHEN("Variable and function are defined")
		{
			const std::string varID("foo");
			const std::string fnID("bar");
			calc.Var(varID);
			calc.Func(fnID, varID);

			THEN("Function changes its value with variable")
			{
				REQUIRE(std::isnan(calc.GetValue(fnID)));
				calc.Let(varID, 42);
				REQUIRE(calc.GetValue(fnID) == 42);
			}
		}

		WHEN("Variables are defined")
		{
			const std::string var1ID("foo");
			const std::string var2ID("bar");
			const std::string fnID("baz");
			calc.Var(var1ID);
			calc.Var(var2ID);

			AND_WHEN("Function is defined")
			{
				calc.Func(fnID, var1ID, Operator::Sum, var2ID);

				THEN("Function can't be redefined")
				{
					REQUIRE_THROWS(calc.Func(fnID, var1ID));
					REQUIRE_THROWS(calc.Func(fnID, var1ID, Operator::Sum, var2ID));
				}
			}

			THEN("Sum operator is functioning properly")
			{
				calc.Func(fnID, var1ID, Operator::Sum, var2ID);

				REQUIRE(std::isnan(calc.GetValue(fnID)));
				calc.Let(var1ID, .42);
				REQUIRE(std::isnan(calc.GetValue(fnID)));
				calc.Let(var2ID, 12.95);
				REQUIRE(calc.GetValue(fnID) == 13.37);
			}

			THEN("Diff operator is functioning properly")
			{
				calc.Func(fnID, var1ID, Operator::Diff, var2ID);

				REQUIRE(std::isnan(calc.GetValue(fnID)));
				calc.Let(var1ID, 13.37);
				REQUIRE(std::isnan(calc.GetValue(fnID)));
				calc.Let(var2ID, .42);
				REQUIRE(calc.GetValue(fnID) == 12.95);
			}

			THEN("Mul operator is functioning properly")
			{
				calc.Func(fnID, var1ID, Operator::Mul, var2ID);

				REQUIRE(std::isnan(calc.GetValue(fnID)));
				calc.Let(var1ID, .42);
				REQUIRE(std::isnan(calc.GetValue(fnID)));
				calc.Let(var2ID, 1000);
				REQUIRE(calc.GetValue(fnID) == 420);
			}

			THEN("Div operator is functioning properly")
			{
				calc.Func(fnID, var1ID, Operator::Div, var2ID);

				REQUIRE(std::isnan(calc.GetValue(fnID)));
				calc.Let(var1ID, 420);
				REQUIRE(std::isnan(calc.GetValue(fnID)));
				calc.Let(var2ID, 1000);
				REQUIRE(calc.GetValue(fnID) == .42);
				calc.Let(var2ID, 0);
				REQUIRE(std::isnan(calc.GetValue(fnID)));
			}
		}
	}
}

SCENARIO("Calculating circle radius")
{
	GIVEN("A calculator")
	{
		CCalculator calc;

		THEN("Radius of circle can be calculated")
		{
			const double radius1 = 10;
			const double radius2 = 20;
			const double pi = 4 * std::atan(1);

			calc.Let("radius", radius1);
			calc.Let("pi", pi);
			calc.Func("radiusSquared", "radius", Operator::Mul, "radius");
			calc.Func("area", "pi", Operator::Mul, "radiusSquared");
			REQUIRE(calc.GetValue("area") == pi * radius1 * radius1);

			calc.Let("radius", radius2);
			REQUIRE(calc.GetValue("area") == pi * radius2 * radius2);
		}
	}
}

std::string GetFibID(int id)
{
	std::ostringstream buf;
	buf << "fib" << id;
	return buf.str();
}

void CheckFibonacciSequence(const CCalculator& calc, int count, int a, int b)
{
	REQUIRE(calc.GetValue("fib0") == a);
	REQUIRE(calc.GetValue("fib1") == b);

	int c;
	for (int i = 2; i < count; i++)
	{
		c = a + b;
		a = b;
		b = c;

		REQUIRE(calc.GetValue(GetFibID(i)) == b);
	}
}

void TestFibonacciSequence(CCalculator& calc, int count)
{
	calc.Let("v0", 0);
	calc.Let("v1", 1);

	calc.Func("fib0", "v0");
	calc.Func("fib1", "v1");
	for (int i = 2; i < count; i++)
	{
		calc.Func(GetFibID(i), GetFibID(i - 1), Operator::Sum, GetFibID(i - 2));
	}

	CheckFibonacciSequence(calc, count, 0, 1);

	calc.Let("v0", 1);
	CheckFibonacciSequence(calc, count, 1, 1);
}

SCENARIO("Calculating Fibonacci sequence")
{
	GIVEN("A calculator")
	{
		CCalculator calc;

		THEN("Fibonacci sequence can be calculated")
		{
			TestFibonacciSequence(calc, 5);
		}
	}
}

SCENARIO("Memoization optimizations")
{
	GIVEN("A calculator")
	{
		CCalculator calc;

		THEN("Fibonacci sequence can be calculated for large indicies")
		{
			TestFibonacciSequence(calc, 25);
		}
	}
}
