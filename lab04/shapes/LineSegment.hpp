#pragma once

#include "Point.hpp"
#include "Shape.hpp"

class CLineSegment final
	: public CShape
{
public:
	CLineSegment(const CPoint& a, const CPoint& b, const CColor& outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	double GetLength() const;
	CPoint GetPointA() const;
	CPoint GetPointB() const;

	void Draw(ICanvas&) override;

protected:
	std::string GetName() const override;
	std::string FieldsToString(int precision = 2) const override;

private:
	CPoint m_a;
	CPoint m_b;
};
