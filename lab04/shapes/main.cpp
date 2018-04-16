#include "Shapes.hpp"
#include "Visualization.hpp"

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
