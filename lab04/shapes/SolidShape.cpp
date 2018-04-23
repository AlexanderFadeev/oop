#include "SolidShape.hpp"
#include <iomanip>
#include <sstream>

CColor CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

CColor CSolidShape::GetOutlineColor() const
{
	return CShape::GetOutlineColor(); 
}

CSolidShape::CSolidShape(const CColor& outlineColor, const CColor& fillColor)
	: CShape(outlineColor)
	, m_fillColor(fillColor)
{
}

std::string CSolidShape::FieldsToString(int precision) const
{
	std::ostringstream buf;

	buf << CShape::FieldsToString(precision);
	buf << "\tfill color: " << m_fillColor.ToString() << ",\n";

	return buf.str();
}
