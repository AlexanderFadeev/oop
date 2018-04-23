#include "Rectangle.hpp"
#include <iomanip>
#include <sstream>

CRectangle::CRectangle(const CPoint& a, const CPoint& b, const CColor& outlineColor, const CColor& fillColor)
	: CSolidShape(outlineColor, fillColor)
	, m_leftTop(a)
	, m_rightBot(b)
{
	Order(m_leftTop.x, m_rightBot.x);
	Order(m_leftTop.y, m_rightBot.y);
}

double CRectangle::GetArea() const
{
	return GetWidth() * GetHeigth();
}

double CRectangle::GetPerimeter() const
{
	return 2 * (GetWidth() + GetHeigth());
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return m_rightBot;
}

double CRectangle::GetWidth() const
{
	return m_rightBot.x - m_leftTop.x;
}

double CRectangle::GetHeigth() const
{
	return m_rightBot.y - m_leftTop.y;
}

std::string CRectangle::ToString(int precision) const
{
	std::ostringstream buf;
	buf << std::setprecision(precision) << std::fixed;

	buf << "Rectangle {\n"
		<< FieldsToString(precision)
		<< "\tleft top vertex: " << m_leftTop.ToString(precision) << ",\n"
		<< "\tright bottom vertex: " << m_rightBot.ToString(precision) << ",\n"
		<< "\twidth: " << GetWidth() << ",\n"
		<< "\theight: " << GetHeigth() << ",\n"
		<< "}";

	return buf.str();
}

void CRectangle::Draw(ICanvas& canvas)
{
	CPoint rightTop{ m_rightBot.x, m_leftTop.y };
	CPoint leftBot{ m_leftTop.x, m_rightBot.y };

	canvas.FillPolygon({ m_leftTop, rightTop, m_rightBot, leftBot }, m_fillColor);
	canvas.DrawLine(m_leftTop, rightTop, m_outlineColor);
	canvas.DrawLine(rightTop, m_rightBot, m_outlineColor);
	canvas.DrawLine(m_rightBot, leftBot, m_outlineColor);
	canvas.DrawLine(leftBot, m_leftTop, m_outlineColor);
}

template <typename T>
inline void CRectangle::Order(T& a, T& b)
{
	if (a > b)
	{
		std::swap(a, b);
	}
}
