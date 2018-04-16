#include "Canvas.hpp"
#include "Color.hpp"
#include "LineSegment.hpp"
#include "Point.hpp"
#include "ShapeFactory.hpp"
#include "Triangle.hpp"
#include "catch.hpp"
#include <sstream>

#pragma warning(push)
#pragma warning(disable : 4100)
#include "fakeit.hpp"
#pragma warning(pop)

using namespace fakeit;

void InitCanvasMock(Mock<ICanvas>& mock)
{
	Fake(Method(mock, DrawLine));
	Fake(Method(mock, FillPolygon));
	Fake(Method(mock, DrawCircle));
	Fake(Method(mock, FillCircle));
}

const std::string g_expectedLineToString =
	R"(LineSegment {
	area: 0.00,
	perimeter: 10.00,
	outline color: #FFFFFF,
	point A: ( 0.50, 0.50 ),
	point B: ( 3.50, 4.50 ),
	length: 5.00,
})";

const std::string g_expectedTriangleToString =
	R"(Triangle {
	area: 6.00,
	perimeter: 12.00,
	outline color: #FFFFFF,
	fill color: #ABCDEF,
	vertex A: ( 0.50, 0.50 ),
	vertex B: ( 3.50, 4.50 ),
	vertex C: ( 0.50, 4.50 ),
})";

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
			AND_THEN("Objects can be correctly converted to uint32")
			{
				CHECK(red.ToUInt32() == 0xFF0000FFu);
				CHECK(cyan.ToUInt32() == 0x00FFFFFFu);
				CHECK(sample.ToUInt32() == 0x010203FFu);
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
		THEN("It can be properly converted to uint32")
		{
			CHECK(color.ToUInt32() == 0x012AFFFFu);
		}
	}

	SECTION("Cannot create colors from invalid args")
	{
		CHECK_THROWS(CColor(256, 0, 0));
		CHECK_THROWS(CColor(0, 256, 0));
		CHECK_THROWS(CColor(0, 0, 256));
		CHECK_THROWS(CColor("12345"));
		CHECK_THROWS(CColor("1234567"));
		CHECK_THROWS(CColor("G00000"));
		CHECK_THROWS(CColor("##123456"));
	}
}

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

				CHECK(g_expectedLineToString == line.ToString());
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

SCENARIO("Triangle")
{

	GIVEN("A Triangle")
	{
		const CPoint a{ .5, .5 };
		const CPoint b{ 3.5, 4.5 };
		const CPoint c{ .5, 4.5 };
		const CColor outlineColor("ffffff");
		const CColor fillColor("abcdef");
		const auto perimeter = 12;
		const auto area = 6;

		CTriangle triangle(a, b, c, outlineColor, fillColor);

		THEN("It is properly initialized")
		{
			CHECK(a == triangle.GetVertexA());
			CHECK(b == triangle.GetVertexB());
			CHECK(c == triangle.GetVertexC());
			CHECK(outlineColor == triangle.GetOutlineColor());
			CHECK(fillColor == triangle.GetFillColor());

			AND_THEN("It has correct property values")
			{
				CHECK(perimeter == triangle.GetPerimeter());
				CHECK(area == triangle.GetArea());
			}
			AND_THEN("It is properly converted to string")
			{

				CHECK(g_expectedTriangleToString == triangle.ToString());
			}
		}

		THEN("It is drawn properly")
		{
			Mock<ICanvas> mock;
			InitCanvasMock(mock);

			triangle.Draw(mock.get());

			Verify(Method(mock, FillPolygon).Using(std::vector<CPoint>{ a, b, c }, fillColor)).Once();
			VerifyNoOtherInvocations(mock);
		}
	}
}

SCENARIO("Shape Factory")
{
	GIVEN("A Shape Factory with valid input data")
	{

		const std::string validFactoryInputData =
			R"(line 0.5 .5 3.5 4.5 #FFFFFF
			   triangle .5 .5 3.5 4.5 .5 4.5 ffffff abcdef)";

		const std::vector<std::string> expectedShapesToString{
			g_expectedLineToString,
			g_expectedTriangleToString,
		};
		auto shapesCount = expectedShapesToString.size();

		std::istringstream iss(validFactoryInputData);
		CShapeFactory factory(iss);

		THEN("It can create shapes")
		{
			CShapeFactory::ShapePtrs shapes;
			REQUIRE_NOTHROW(shapes = factory.GetAllShapes());

			AND_THEN("It creates right amount of shapes")
			{
				REQUIRE(shapes.size() == shapesCount);

				AND_THEN("All shapes are initialized with correct property values")
				{
					for (size_t index = 0; index < shapesCount; index++)
					{
						CHECK(shapes[index]->ToString() == expectedShapesToString[index]);
					}
				}
			}
		}
	}
}
