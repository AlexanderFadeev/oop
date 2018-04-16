#include "Shapes.hpp"
#include "Visualization.hpp"

void ProcessShapes(std::istream& input, std::ostream& output);
void PrintLargest(std::ostream& output, ShapePtrs& shapes);
void Visualize(ShapePtrs& shapes);

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

void ProcessShapes(std::istream& input, std::ostream& output)
{
	CShapeFactory factory(input);
	auto shapes = factory.GetAllShapes();

	PrintLargest(output, shapes);
	Visualize(shapes);
}

void PrintLargest(std::ostream& output, ShapePtrs& shapes)
{
	auto shapeWithLargestArea = FindShapeWithLargestArea(shapes);
	auto shapeWithLargestPerimeter = FindShapeWithLargestPerimeter(shapes);

	output << "Shape with largest area:\n"
		   << shapeWithLargestArea->ToString() << '\n'
		   << "Shape with largest perimeter:\n"
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
