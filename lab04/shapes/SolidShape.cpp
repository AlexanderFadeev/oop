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

std::string CSolidShape::ToString(int precision) const
{
	return CShape::ToString(precision);
}

CSolidShape::CSolidShape(const CColor& outlineColor, const CColor& fillColor)
	: CShape(outlineColor)
	, m_fillColor(fillColor)
{
}

std::string CSolidShape::FieldsToString(int precision) const
{
	std::ostringstream buf;

	buf << "\tfill color: " << m_fillColor.ToString() << ",\n"
		<< SolidFieldsToString(precision);

	return buf.str();
}
