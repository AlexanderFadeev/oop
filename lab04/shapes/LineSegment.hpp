#pragma once

#include "CanvasDrawable.hpp"
#include "Point.hpp"
#include "Shape.hpp"

class CLineSegment final
	: public IShape
	, public ICanvasDrawable
{
public:
	CLineSegment(const CPoint& a, const CPoint& b, const std::string& outlineColor);
	CLineSegment(const CPoint& a, const CPoint& b, const CColor& outlineColor);
	~CLineSegment() override = default;

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
