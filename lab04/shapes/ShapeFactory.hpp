#pragma once

#include "IShape.hpp"
#include <functional>
#include <iostream>
#include <map>
#include <memory>

class CShapeFactory final
{
public:
	using ShapePtr = std::shared_ptr<IShape>;

	static ShapePtr CreateShape(const std::string&);
private:
	using GetShapeFunction = std::function<ShapePtr(std::istream&)>;

	static const std::map<std::string, GetShapeFunction> m_getShapeFunctionMapping;

	static ShapePtr CreateLine(std::istream&);
	static ShapePtr CreateTriangle(std::istream&);
	static ShapePtr CreateRectangle(std::istream&);
	static ShapePtr CreateCircle(std::istream&);
};
