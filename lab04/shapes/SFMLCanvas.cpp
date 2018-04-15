#include "SFMLCanvas.hpp"

CSFMLCanvas::CSFMLCanvas(unsigned w, unsigned h, const std::string& name)
	: m_window(sf::VideoMode({ w, h }), name)
{
}

void CSFMLCanvas::DrawLine(const CPoint& a, const CPoint& b, const CColor& c)
{
}

void CSFMLCanvas::FillPolygon(const std::vector<CPoint>&, const CColor&)
{
}

void CSFMLCanvas::DrawCircle(const CPoint&, double, const CColor&)
{
}

void CSFMLCanvas::FillCircle(const CPoint&, double, const CColor&)
{
}
