#include "Shapes.hpp"

ShapePtr FindShapeWithLargestArea(ShapePtrs& shapes)
{
	return *std::max_element(shapes.begin(), shapes.end(), [](auto a, auto b) {
		return a->GetArea() < b->GetArea();
	});
}

ShapePtr FindShapeWithSmallestPerimeter(ShapePtrs& shapes)
{
	return *std::min_element(shapes.begin(), shapes.end(), [](auto a, auto b) {
		return a->GetPerimeter() < b->GetPerimeter();
	});
}

ShapePtr GetShape(std::istream& input)
{

	std::string line;
	if (!std::getline(input, line))
	{
		return nullptr;
	}

	return CShapeFactory::CreateShape(line);
}

ShapePtrs GetAllShapes(std::istream& input)
{
	std::vector<ShapePtr> vec;

	while (auto shapePtr = GetShape(input))
	{
		vec.push_back(shapePtr);
	}

	return vec;
}
