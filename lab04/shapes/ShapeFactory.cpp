#include "ShapeFactory.hpp"
#include "Circle.hpp"
#include "LineSegment.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include <sstream>

CShapeFactory::ShapePtr CShapeFactory::CreateShape(const std::string& line)
{
	std::istringstream iss(line);
	std::string type;

	iss >> type;
	if (type.empty())
	{
		throw std::invalid_argument("Expected shape type");
	}

	const auto& mapping = m_getShapeFunctionMapping;
	auto fn = mapping.find(type);
	if (fn == mapping.end())
	{
		std::stringstream buf;
		buf << "Wrong shape type: " << type;
		throw std::invalid_argument(buf.str());
	}

	return fn->second.operator()(iss);
}

const std::map<std::string, CShapeFactory::GetShapeFunction> CShapeFactory::m_getShapeFunctionMapping{
	{ "line", &CreateLine },
	{ "triangle", &CreateTriangle },
	{ "rectangle", &CreateRectangle },
	{ "circle", &CreateCircle },
};

CShapeFactory::ShapePtr CShapeFactory::CreateLine(std::istream& input)
{
	CPoint a;
	CPoint b;
	CColor outlineColor;

	input >> a >> b >> outlineColor;

	return std::make_shared<CLineSegment>(a, b, outlineColor);
}

CShapeFactory::ShapePtr CShapeFactory::CreateTriangle(std::istream& input)
{
	CPoint a;
	CPoint b;
	CPoint c;
	CColor outlineColor;
	CColor fillColor;

	input >> a >> b >> c >> outlineColor >> fillColor;
	return std::make_shared<CTriangle>(a, b, c, outlineColor, fillColor);
}

CShapeFactory::ShapePtr CShapeFactory::CreateRectangle(std::istream& input)
{
	CPoint a;
	CPoint b;
	CColor outlineColor;
	CColor fillColor;

	input >> a >> b >> outlineColor >> fillColor;
	return std::make_shared<CRectangle>(a, b, outlineColor, fillColor);
}

CShapeFactory::ShapePtr CShapeFactory::CreateCircle(std::istream& input)
{
	CPoint center;
	double radius;
	CColor outlineColor;
	CColor fillColor;

	input >> center >> radius >> outlineColor >> fillColor;
	return std::make_shared<CCircle>(center, radius, outlineColor, fillColor);
}
