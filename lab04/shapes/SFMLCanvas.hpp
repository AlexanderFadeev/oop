#pragma once

#include "Canvas.hpp"
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <string>

class CSFMLCanvas final
	: public ICanvas
{
public:
	CSFMLCanvas(unsigned width, unsigned height, const std::string& name);

	void DrawLine(const CPoint&, const CPoint&, const CColor&) override;
	void FillPolygon(const std::vector<CPoint>&, const CColor&) override;
	void DrawCircle(const CPoint&, double, const CColor&) override;
	void FillCircle(const CPoint&, double, const CColor&) override;

	void Display();
	void WaitForCloseEvent();

private:
	sf::RenderWindow m_window;

	static sf::Color Color(const CColor&);
	static sf::Vector2f Vector2f(const CPoint&);
	static sf::Vector2f GetCirclePos(const CPoint&, double);
};
