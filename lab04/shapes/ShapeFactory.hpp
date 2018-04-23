#pragma once

#include "IShape.hpp"
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

class CShapeFactory final
{
public:
	using ShapePtr = std::shared_ptr<IShape>;
	using ShapePtrs = std::vector<ShapePtr>;

	CShapeFactory(std::istream&);

	ShapePtr GetShape() const;
	ShapePtrs GetAllShapes() const;

private:
	using GetShapeFunction = std::function<ShapePtr(std::istream&)>;

	std::istream& m_input;
	static const std::map<std::string, GetShapeFunction> m_getShapeFunctionMapping;

	static ShapePtr GetLine(std::istream&);
	static ShapePtr GetTriangle(std::istream&);
	static ShapePtr GetRectangle(std::istream&);
	static ShapePtr GetCircle(std::istream&);
};
