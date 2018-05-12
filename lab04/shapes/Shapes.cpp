#include "Shapes.hpp"

ShapePtr FindShapeWithLargestArea(ShapePtrs& shapes)
{
	return *std::max_element(shapes.begin(), shapes.end(), [](auto a, auto b) {
		return a->GetArea() < b->GetArea();
	});
	;
}

ShapePtr FindShapeWithSmallestPerimeter(ShapePtrs& shapes)
{
	return *std::min_element(shapes.begin(), shapes.end(), [](auto a, auto b) {
		return a->GetPerimeter() < b->GetPerimeter();
	});
}

ShapePtrs GetAllShapes(std::istream& input)
{
	std::vector<ShapePtr> vec;

	std::string line;
	while (std::getline(input, line))
	{
		auto shapePtr = CShapeFactory::CreateShape(line);
		vec.push_back(shapePtr);
	}

	return vec;
}
