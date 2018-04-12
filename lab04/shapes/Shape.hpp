#pragma once

#include <string>

class IShape
{
public:
	virtual ~IShape() = default;

	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString(int) const = 0;
	std::string GetOutlineColor() const;

protected:
	IShape(const std::string& outlineColor);
	std::string FieldsToString(int precision = 2) const;

private:
	std::string m_outlineColor;
};
