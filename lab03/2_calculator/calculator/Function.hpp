#pragma once

#include "Identifier.hpp"
#include <functional>
#include <map>
#include <optional>

class CFunction
	: public CIdentifier
{
public:
	using IDWPtr = CIdentifier::WeakPtr;

	enum class Operator;
	
	static std::shared_ptr<CFunction> New(const IDWPtr& identifier);
	static std::shared_ptr<CFunction> New(const IDWPtr& operand1, Operator op, const IDWPtr& operand2);

private:
	CFunction(const IDWPtr& identifier);
	CFunction(const IDWPtr& operand1, Operator op, const IDWPtr& operand2);

	void Init();

	double CalcValue() const;

	static const std::map<Operator, std::function<double(double, double)>> m_operatorToFunctionMapping;

	std::optional<Operator> m_operator;
	IDWPtr m_operand1WPtr;
	IDWPtr m_operand2WPtr;

};

enum class CFunction::Operator
{
	Sum,
	Diff,
	Mul,
	Div,
};
