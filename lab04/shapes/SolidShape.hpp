#pragma once

#include "ISolidShape.hpp"
#include "Shape.hpp"

class CSolidShape
	: public CShape
	, public virtual ISolidShape
{
public:
	CColor GetFillColor() const override;
	CColor GetOutlineColor() const override; // Fix for warning 4250: `inherits via dominance`

protected:
	CSolidShape(const CColor& outlineColor, const CColor& fillColor);

	std::string FieldsToString(int precision = 2) const;

	CColor m_fillColor;
};
