#pragma once

#include "Identifier.hpp"
#include <functional>
#include <map>
#include <memory>
#include <optional>

class CFunction : public CIdentifier
{
public:
	enum class Operator;

	CFunction(std::shared_ptr<CIdentifier> identifier);
	CFunction(std::shared_ptr<CIdentifier> operand1, Operator op, std::shared_ptr<CIdentifier> operand2);

	double GetValue() const override;

private:
	static const std::map<Operator, std::function<double(double, double)>> m_operatorToFunctionMapping;

	std::optional<Operator> m_operator;
	std::shared_ptr<CIdentifier> m_operand1;
	std::shared_ptr<CIdentifier> m_operand2;
};

enum class CFunction::Operator
{
	Sum,
	Diff,
	Mul,
	Div,
};
