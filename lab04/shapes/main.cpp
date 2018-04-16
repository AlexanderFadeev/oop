#include "LineSegment.hpp"
#include "SFMLCanvas.hpp"
#include "ShapeFactory.hpp"
#include "Shapes.hpp"

void PrintLargest(std::ostream& output, ShapePtrs shapes)
{
	auto shapeWithLargestArea = FindShapeWithLargestProperty(shapes, &IShape::GetArea);
	auto shapeWithLargestPerimeter = FindShapeWithLargestProperty(shapes, &IShape::GetArea);

	output << "Shape with larges area:\n"
		   << shapeWithLargestArea->ToString() << '\n'
		   << "Shape with larges perimeter:\n"
		   << shapeWithLargestPerimeter->ToString() << std::endl;

	if (!output)
	{
		throw std::runtime_error("Failed to write to output");
	}
}

void Visualize(ShapePtrs& shapes)
{
	CSFMLCanvas canvas(800, 450, "Shapes");
	DrawAll(canvas, shapes);
	canvas.Display();
	canvas.WaitForCloseEvent();
}

void ProcessShapes(std::istream& input, std::ostream& output)
{
	CShapeFactory factory(input);
	auto shapes = factory.GetAllShapes();

	PrintLargest(output, shapes);
	Visualize(shapes);
}

int main() try
{
	ProcessShapes(std::cin, std::cout);
	return 0;
}
catch (std::exception& e)
{
	std::cerr << e.what();
	return 1;
}
catch (...)
{
	std::cerr << "Unknown exception";
	return 1;
}
