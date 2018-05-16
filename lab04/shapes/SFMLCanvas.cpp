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
	circle.setPosition(GetCirclePos(center, radius));
	circle.setFillColor(sf::Color(0, 0, 0, 0));
	circle.setOutlineColor(Color(color));
	circle.setOutlineThickness(1);

	m_window.draw(circle);
}

void CSFMLCanvas::FillCircle(const CPoint& center, double radius, const CColor& color)
{
	sf::CircleShape circle(static_cast<float>(radius));
	circle.setPosition(GetCirclePos(center, radius));
	circle.setFillColor(Color(color));

	m_window.draw(circle);
}

void CSFMLCanvas::AddDrawable(CSFMLCanvas::DrawablePtr pDrawable)
{
	m_drawables.push_back(pDrawable);
}

void CSFMLCanvas::RunEventLoop()
{
	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;

			case sf::Event::Resized:
				Redraw();
				break;
			}
		}
	}
}

void CSFMLCanvas::Redraw()
{
	for (auto& ptr : m_drawables)
	{
		ptr->Draw(*this);
	}

	m_window.display();
}

sf::Color CSFMLCanvas::Color(const CColor& color)
{
	return sf::Color(color.ToUInt32());
}

sf::Vector2f CSFMLCanvas::Vector2f(const CPoint& point)
{
	return sf::Vector2f(static_cast<float>(point.x), static_cast<float>(point.y));
}

sf::Vector2f CSFMLCanvas::GetCirclePos(const CPoint& center, double radius)
{
	CPoint pos{ center.x - radius, center.y - radius };
	return Vector2f(pos);
}
