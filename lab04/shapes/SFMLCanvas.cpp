#include "SFMLCanvas.hpp"

CSFMLCanvas::CSFMLCanvas(unsigned w, unsigned h, const std::string& name)
	: m_window(sf::VideoMode({ w, h }), name)
{
}

void CSFMLCanvas::DrawLine(const CPoint& a, const CPoint& b, const CColor& color)
{
	sf::Vertex line[2];

	line[0].position = Vector2f(a);
	line[0].color = Color(color);
	line[1].position = Vector2f(b);
	line[1].color = Color(color);

	m_window.draw(line, 2, sf::PrimitiveType::Lines);
}

void CSFMLCanvas::FillPolygon(const std::vector<CPoint>& points, const CColor& color)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());
	for (size_t index = 0; index < points.size(); index++)
	{
		polygon.setPoint(index, Vector2f(points[index]));
	}

	polygon.setFillColor(Color(color));
	m_window.draw(polygon);
}

void CSFMLCanvas::DrawCircle(const CPoint& center, double radius, const CColor& color)
{
	sf::CircleShape circle(static_cast<float>(radius));
	circle.setPosition(Vector2f(center));
	circle.setFillColor(sf::Color(0, 0, 0, 0));
	circle.setOutlineColor(Color(color));
	circle.setOutlineThickness(1);

	m_window.draw(circle);
}

void CSFMLCanvas::FillCircle(const CPoint& center, double radius, const CColor& color)
{
	sf::CircleShape circle(static_cast<float>(radius));
	circle.setPosition(Vector2f(center));
	circle.setFillColor(Color(color));

	m_window.draw(circle);
}

void CSFMLCanvas::Display()
{
	m_window.display();
}

void CSFMLCanvas::WaitForCloseEvent()
{
	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}
		}
	}
}

sf::Color CSFMLCanvas::Color(const CColor& color)
{
	return sf::Color(color.ToUInt32());
}

sf::Vector2f CSFMLCanvas::Vector2f(const CPoint& point)
{
	return sf::Vector2f(static_cast<float>(point.x), static_cast<float>(point.y));
}
