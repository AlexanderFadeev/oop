#pragma once

#include "IShape.hpp"


class CShape
	: public virtual IShape
{
public:
	CColor GetOutlineColor() const override;

protected:
	CShape(const CColor& outlineColor);

	std::string FieldsToString(int precision = 2) const;

	CColor m_outlineColor;
};