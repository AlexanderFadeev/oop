#include "Function.hpp"
#include <exception>
#include <limits>

CFunction::CFunction(std::shared_ptr<CIdentifier> id)
	: m_operand1(id)
{
}

CFunction::CFunction(std::shared_ptr<CIdentifier> operand1, Operator op, std::shared_ptr<CIdentifier> operand2)
	: m_operand1(operand1)
	, m_operator(op)
	, m_operand2(operand2)
{
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

double CFunction::GetValue() const
{
	if (m_operator)
	{
		auto fn = m_operatorToFunctionMapping.at(*m_operator);
		double val1 = m_operand1->GetValue();
		double val2 = m_operand2->GetValue();

		return fn(val1, val2);
	}

	return m_operand1->GetValue();
}
