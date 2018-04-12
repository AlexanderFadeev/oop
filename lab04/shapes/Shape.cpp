#include "Shape.hpp"
#include <iomanip>
#include <sstream>

std::string IShape::GetOutlineColor() const
{
	return m_outlineColor;
}

IShape::IShape(const std::string& outlineColor)
	: m_outlineColor(outlineColor)
{
}

std::string IShape::FieldsToString(int precision) const
{
	std::ostringstream buf;
	buf << std::setprecision(precision);

	buf << "\tarea: " << GetArea() << ",\n"
		<< "\tperimeter: " << GetPerimeter() << ",\n"
		<< "\toutline color: " << GetOutlineColor() << ",\n";

	return buf.str();
}
