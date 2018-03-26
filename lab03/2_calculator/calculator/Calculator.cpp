#include "Calculator.hpp"

double CCalculator::GetValue(const std::string& id) const
{
	ThrowIfNotDefined(id);

	return m_identifiers.at(id)->GetValue();
}

void CCalculator::Var(const std::string& id)
{
	ThrowIfNotValid(id);
	ThrowIfDefined(id);

	std::shared_ptr<CVariable> variable(new CVariable);
	m_identifiers[id] = variable;
	m_variables[id] = variable;
}

void CCalculator::Let(const std::string& id, double value)
{
	if (!IsIdentifierDefined(id, m_variables))
	{
		Var(id);
	}

	m_variables.at(id)->SetValue(value);
}

void CCalculator::Let(const std::string& id1, const std::string& id2)
{
	ThrowIfNotDefined(id2, m_variables);

	double value = GetValue(id2);
	Let(id1, value);
}

void CCalculator::Func(const std::string& fnID, const std::string& id)
{
	ThrowIfNotValid(fnID);
	ThrowIfDefined(fnID);
	ThrowIfNotDefined(id);

	std::shared_ptr<CFunction> function = std::make_shared<CFunction>(m_identifiers.at(id));
	m_identifiers[fnID] = function;
	m_functions[fnID] = function;
}

using Operator = CFunction::Operator;

void CCalculator::Func(const std::string& fnID, const std::string& id1, Operator op, const std::string& id2)
{
	ThrowIfNotValid(fnID);
	ThrowIfDefined(fnID);
	ThrowIfNotDefined(id1);
	ThrowIfNotDefined(id2);

	auto function = std::make_shared<CFunction>(m_identifiers.at(id1), op, m_identifiers.at(id2));
	m_identifiers[fnID] = function;
	m_functions[fnID] = function;
}

const std::regex CCalculator::m_identifierRegex(R"(^[_A-Za-z]\w*$)");

bool CCalculator::IsIdentifierValid(const std::string& id) const
{
	return std::regex_match(id, m_identifierRegex);
}

template <typename T>
bool CCalculator::IsIdentifierDefined(const std::string& id, const IDMapping<T>& where) const
{
	return where.find(id) != where.end();
}

bool CCalculator::IsIdentifierDefined(const std::string& id) const
{
	return IsIdentifierDefined(id, m_identifiers);
}

void CCalculator::ThrowIfNotValid(const std::string& id) const
{
	if (!IsIdentifierValid(id))
	{
		throw std::exception("Identifier is not valid");
	}
}

template <typename T>
void CCalculator::ThrowIfDefined(const std::string& id, const IDMapping<T>& where) const
{
	if (IsIdentifierDefined(id, where))
	{
		throw std::exception("Identifier is already defined");
	}
}

void CCalculator::ThrowIfDefined(const std::string& id) const
{
	ThrowIfDefined(id, m_identifiers);
}

template <typename T>
void CCalculator::ThrowIfNotDefined(const std::string& id, const IDMapping<T>& where) const
{
	if (!IsIdentifierDefined(id, where))
	{
		throw std::exception("Identifier is not defined");
	}
}

void CCalculator::ThrowIfNotDefined(const std::string& id) const
{
	ThrowIfNotDefined(id, m_identifiers);
}
