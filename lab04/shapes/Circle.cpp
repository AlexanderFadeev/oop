#include "Circle.hpp"
#include <iomanip>
#include <sstream>

CCircle::CCircle(const CPoint& center, double radius, const CColor& outlineColor, const CColor& fillColor)
	: ISolidShape(outlineColor, fillColor)
	, m_center(center)
	, m_radius(radius)
{
}

double CCircle::GetArea() const
{
	return GetPi() * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * GetPi() * m_radius;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

std::string CCircle::ToString(int precision) const
{
	std::ostringstream buf;
	buf << std::setprecision(precision) << std::fixed;

	buf << "Circle {\n"
		<< FieldsToString(precision)
		<< "\tcenter point: " << m_center.ToString(precision) << ",\n"
		<< "\tradius: " << m_radius << ",\n"
		<< "}";

	return buf.str();
}

void CCircle::Draw(ICanvas& canvas)
{
	canvas.FillCircle(m_center, m_radius, m_fillColor);
	canvas.DrawCircle(m_center, m_radius, m_outlineColor);
}

double CCircle::GetPi()
{
	return std::atan(1) * 4;
}
