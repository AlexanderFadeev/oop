#pragma once

#include "IShape.hpp"

class CShape
	: public virtual IShape
{
public:
	CColor GetOutlineColor() const override;
	std::string ToString(int precision = 2) const override;

protected:
	CShape(const CColor& outlineColor);

	virtual std::string GetName() const = 0;
	virtual std::string FieldsToString(int precision = 2) const = 0;

	CColor m_outlineColor;
};