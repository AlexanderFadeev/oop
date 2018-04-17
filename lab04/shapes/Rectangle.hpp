#pragma once

#include "SolidShape.hpp"

class CRectangle : public ISolidShape
{
public:
	CRectangle(const CPoint&, const CPoint&, const CColor&, const CColor&);

	double GetArea() const override;
	double GetPerimeter() const override;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeigth() const;

	std::string ToString(int precision = 2) const override;

	virtual void Draw(ICanvas&) override;

private:
	template <typename T>
	static void Order(T& a, T& b);

	CPoint m_leftTop;
	CPoint m_rightBot;
};
