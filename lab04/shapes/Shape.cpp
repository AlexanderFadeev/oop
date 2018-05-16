#include "Shape.hpp"
#include <iomanip>
#include <sstream>

CColor CShape::GetOutlineColor() const
{
	return m_outlineColor;
}

CShape::CShape(const CColor& outlineColor)
	: m_outlineColor(outlineColor)
{
}

std::string CShape::ToString(int precision) const
{
	std::ostringstream buf;
	buf << std::setprecision(precision) << std::fixed;

	buf << GetName() << " {\n"
		<< "\tarea: " << GetArea() << ",\n"
		<< "\tperimeter: " << GetPerimeter() << ",\n"
		<< "\toutline color: " << m_outlineColor.ToString() << ",\n"
		<< FieldsToString()
		<< "}";

	return buf.str();
}
