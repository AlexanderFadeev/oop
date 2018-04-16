#include "ShapeFactory.hpp"
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
};

CShapeFactory::ShapePtr CShapeFactory::GetLine(std::istream& input)
{
	CPoint a;
	CPoint b;
	CColor c;

	input >> a >> b >> c;

	return std::make_shared<CLineSegment>(a, b, c);
}
