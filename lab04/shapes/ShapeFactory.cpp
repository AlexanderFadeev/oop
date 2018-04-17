#include "ShapeFactory.hpp"
#include "Circle.hpp"
#include "LineSegment.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include <sstream>

CShapeFactory::CShapeFactory(std::istream& input)
	: m_input(input)
{
}

CShapeFactory::ShapePtr CShapeFactory::GetShape() const
{
	std::string line;

	if (!std::getline(m_input, line))
	{
		return {};
	}

	std::istringstream iss(line);
	std::string type;

	iss >> type;

	auto& mapping = m_getShapeFunctionMapping;
	auto fn = mapping.find(type);
	if (fn == mapping.end())
	{
		std::stringstream buf;
		buf << "Wrong shape type: " << type;
		throw std::invalid_argument(buf.str());
	}

	return fn->second.operator()(iss);
}

CShapeFactory::ShapePtrs CShapeFactory::GetAllShapes() const
{
	ShapePtrs result;

	while (auto shape = GetShape())
	{
		result.push_back(shape);
	}

	return result;
}

const std::map<std::string, CShapeFactory::GetShapeFunction> CShapeFactory::m_getShapeFunctionMapping{
	{ "line", &GetLine },
	{ "triangle", &GetTriangle },
	{ "rectangle", &GetRectangle },
	{ "circle", &GetCircle },
};

CShapeFactory::ShapePtr CShapeFactory::GetLine(std::istream& input)
{
	CPoint a;
	CPoint b;
	CColor outlineColor;

	input >> a >> b >> outlineColor;

	return std::make_shared<CLineSegment>(a, b, outlineColor);
}

CShapeFactory::ShapePtr CShapeFactory::GetTriangle(std::istream& input)
{
	CPoint a;
	CPoint b;
	CPoint c;
	CColor outlineColor;
	CColor fillColor;

	input >> a >> b >> c >> outlineColor >> fillColor;
	return std::make_shared<CTriangle>(a, b, c, outlineColor, fillColor);
}

CShapeFactory::ShapePtr CShapeFactory::GetRectangle(std::istream& input)
{
	CPoint a;
	CPoint b;
	CColor outlineColor;
	CColor fillColor;

	input >> a >> b >> outlineColor >> fillColor;
	return std::make_shared<CRectangle>(a, b, outlineColor, fillColor);
}

CShapeFactory::ShapePtr CShapeFactory::GetCircle(std::istream& input)
{
	CPoint center;
	double radius;
	CColor outlineColor;
	CColor fillColor;

	input >> center >> radius >> outlineColor >> fillColor;
	return std::make_shared<CCircle>(center, radius, outlineColor, fillColor);
}
