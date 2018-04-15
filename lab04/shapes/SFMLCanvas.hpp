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

private:
	sf::RenderWindow m_window;
};
