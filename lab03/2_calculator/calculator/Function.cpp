#include "Function.hpp"
#include <exception>
#include <limits>

CFunction::CFunction(std::weak_ptr<CIdentifier> id)
	: m_operand1WPtr(id)
{
}

CFunction::CFunction(std::weak_ptr<CIdentifier> operand1, Operator op, std::weak_ptr<CIdentifier> operand2)
	: m_operand1WPtr(operand1)
	, m_operator(op)
	, m_operand2WPtr(operand2)
{
}

void CFunction::Init()
{
	Uses(m_operand1WPtr);
	if (m_operator)
	{
		Uses(m_operand2WPtr);
	}
}

using Operator = CFunction::Operator;

const std::map<Operator, std::function<double(double, double)>> CFunction::m_operatorToFunctionMapping{
	{ Operator::Sum, [](double a, double b) {
		 return a + b;
	 } },

	{ Operator::Diff, [](double a, double b) {
		 return a - b;
	 } },

	{ Operator::Mul, [](double a, double b) {
		 return a * b;
	 } },

	{ Operator::Div, [](double a, double b) {
		 const double eps = 1e-12;
		 if (std::abs(b) < eps)
		 {
			 return std::numeric_limits<double>::quiet_NaN();
		 }
		 return a / b;
	 } },
};

double CFunction::CalcValue() const
{
	auto operand1SPtr = m_operand1WPtr.lock();
	if (!operand1SPtr)
	{
		throw std::logic_error("Weak pointers to first operand expired");
	}

	if (!m_operator)
	{
		return operand1SPtr->GetValue();
	}

	auto operand2SPtr = m_operand2WPtr.lock();
	if (!operand2SPtr)
	{
		throw std::logic_error("Weak pointers to second operand expired");
	}

	auto fn = m_operatorToFunctionMapping.at(*m_operator);
	double val1 = operand1SPtr->GetValue();
	double val2 = operand2SPtr->GetValue();

	return fn(val1, val2);
}
