#pragma once

#include "CanvasDrawable.hpp"
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

	std::string ToString(int precision = 2) const override;

	void Draw(ICanvas&) override;

private:
	CPoint m_a;
	CPoint m_b;
};
