#include "Shape.hpp"
#include <iomanip>
#include <sstream>

CColor IShape::GetOutlineColor() const
{
	return m_outlineColor;
}

IShape::IShape(const std::string& outlineColor)
	: m_outlineColor(outlineColor)
{
}

IShape::IShape(const CColor& outlineColor)
	: m_outlineColor(outlineColor)
{
}

std::string IShape::FieldsToString(int precision) const
{
	std::ostringstream buf;
	buf << std::setprecision(precision);

	buf << "\tarea: " << GetArea() << ",\n"
		<< "\tperimeter: " << GetPerimeter() << ",\n"
		<< "\toutline color: " << m_outlineColor.ToString() << ",\n";

	return buf.str();
}
