#pragma once

#include "Identifier.hpp"
#include <functional>
#include <map>
#include <optional>

class CFunction
	: public CIdentifier
{
public:
	enum class Operator;

	template <typename... Args>
	static std::shared_ptr<CFunction> New(Args&&... args);

	CFunction(std::shared_ptr<CIdentifier> identifier);
	CFunction(std::shared_ptr<CIdentifier> operand1, Operator op, std::shared_ptr<CIdentifier> operand2);
	void Init();

private:
	double CalcValue() const;

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

template <typename... Args>
inline std::shared_ptr<CFunction> CFunction::New(Args&&... args)
{
	auto ptr = std::make_shared<CFunction>(std::forward<Args>(args)...);
	ptr->Init();
	return ptr;
}
