#pragma once

#include "Shape.hpp"

class ISolidShape
	: public IShape
{
public:
	CColor GetFillColor() const;

protected:
	ISolidShape(const std::string& outlineColor, const std::string& fillColor);
	ISolidShape(const CColor& outlineColor, const CColor& fillColor);

	std::string FieldsToString(int precision = 2) const;

	CColor m_fillColor;
};
