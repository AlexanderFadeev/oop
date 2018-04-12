#include "Canvas.hpp"
#include "Color.hpp"
#include "LineSegment.hpp"
#include "Point.hpp"
#include "catch.hpp"
#include "fakeit.hpp"

using namespace fakeit;

void InitCanvasMock(Mock<ICanvas>& mock)
{
	Fake(Method(mock, DrawLine));
	Fake(Method(mock, FillPolygon));
	Fake(Method(mock, DrawCircle));
	Fake(Method(mock, FillCircle));
}

SCENARIO("Colors")
{
	GIVEN("Valid hex colors")
	{
		std::string redHex = "Ff0000";
		std::string cyanHex = "00fFFf";
		std::string sampleHex = "#010203";

		THEN("They can be used to create color objects")
		{
			CColor red(redHex);
			CColor cyan(cyanHex);
			CColor sample(sampleHex);

			AND_THEN("Objects can be correctly converted back to strings")
			{
				CHECK(red.ToString() == "#FF0000");
				CHECK(cyan.ToString() == "#00FFFF");
				CHECK(sample.ToString() == "#010203");
			}
		}
	}

	GIVEN("A color created from RGB int values")
	{
		CColor color(1, 42, 255);

		THEN("It can be properly converted to string")
		{
			CHECK(color.ToString() == "#012AFF");
		}
	}

	SECTION("Cannot create colors from invalid args")
	{
		CHECK_THROWS(CColor(-1, 0, 0));
		CHECK_THROWS(CColor(256, 0, 0));
		CHECK_THROWS(CColor("12345"));
		CHECK_THROWS(CColor("1234567"));
		CHECK_THROWS(CColor("G00000"));
		CHECK_THROWS(CColor("##123456"));
	}
}

const std::string expectedLineToString =
	R"(LineSegment {
	area: 0,
	perimeter: 10,
	outline color: #FFFFFF,
	point A: ( 0.5, 0.5 ),
	point B: ( 3.5, 4.5 ),
	length: 5,
}
)";

SCENARIO("Line Segment")
{
	GIVEN("A Line Segment")
	{
		const CPoint a{ .5, .5 };
		const CPoint b{ 3.5, 4.5 };
		const CColor color("ffffff");
		const auto len = 5;

		CLineSegment line(a, b, color);

		THEN("It is properly initialized")
		{
			CHECK(a == line.GetPointA());
			CHECK(b == line.GetPointB());
			CHECK(color == line.GetOutlineColor());

			AND_THEN("It has correct property values")
			{
				CHECK(len == line.GetLength());
				CHECK(2 * len == line.GetPerimeter());
				CHECK(0 == line.GetArea());
			}
			AND_THEN("It is properly converted to string")
			{

				CHECK(expectedLineToString == line.ToString());
			}
		}

		THEN("It is drawn properly")
		{
			Mock<ICanvas> mock;
			InitCanvasMock(mock);

			line.Draw(mock.get());

			Verify(Method(mock, DrawLine).Using(a, b, color)).Once();
			VerifyNoOtherInvocations(mock);
		}
	}
}
