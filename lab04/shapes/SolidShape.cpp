#include "SolidShape.hpp"
#include <iomanip>
#include <sstream>

CColor ISolidShape::GetFillColor() const
{
	return m_fillColor;
}

ISolidShape::ISolidShape(const std::string& outlineColor, const std::string& fillColor)
	: IShape(outlineColor)
	, m_fillColor(fillColor)
{
}

ISolidShape::ISolidShape(const CColor& outlineColor, const CColor& fillColor)
	: IShape(outlineColor)
	, m_fillColor(fillColor)
{
}

std::string ISolidShape::FieldsToString(int precision) const
{
	std::ostringstream buf;

	buf << IShape::FieldsToString(precision);
	buf << "\tfill color: " << m_fillColor.ToString() << ",\n";

	return buf.str();
}
