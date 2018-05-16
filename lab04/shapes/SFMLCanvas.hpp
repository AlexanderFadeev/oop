#pragma once

#include "ICanvas.hpp"
#include "ICanvasDrawable.hpp"
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <memory>
#include <string>
#include <vector>

class CSFMLCanvas final
	: public ICanvas
{
	using DrawablePtr = std::shared_ptr<ICanvasDrawable>;

public:
	CSFMLCanvas(unsigned width, unsigned height, const std::string& name);

	void DrawLine(const CPoint&, const CPoint&, const CColor&) override;
	void FillPolygon(const std::vector<CPoint>&, const CColor&) override;
	void DrawCircle(const CPoint&, double, const CColor&) override;
	void FillCircle(const CPoint&, double, const CColor&) override;

	void AddDrawable(DrawablePtr);
	void RunEventLoop();
	void Redraw();

private:

	static sf::Color Color(const CColor&);
	static sf::Vector2f Vector2f(const CPoint&);
	static sf::Vector2f GetCirclePos(const CPoint&, double);

	sf::RenderWindow m_window;
	std::vector<DrawablePtr> m_drawables;
};
