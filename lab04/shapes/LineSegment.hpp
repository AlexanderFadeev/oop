#pragma once

#include "Point.hpp"
#include "Shape.hpp"

class CLineSegment final
	: public IShape
{
public:
	CLineSegment(const CPoint& a, const CPoint& b, const std::string& outlineColor);
	~CLineSegment() override = default;

	std::string ToString(int precision = 2) const override;
	double GetArea() const override;
	double GetPerimeter() const override;
	double GetLength() const;
	CPoint GetPointA() const;
	CPoint GetPointB() const;

private:
	CPoint m_a;
	CPoint m_b;
};
