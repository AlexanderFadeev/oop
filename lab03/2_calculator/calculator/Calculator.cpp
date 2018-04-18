#include "Calculator.hpp"

namespace
{

template <typename T>
using IDMapping = std::map<std::string, std::shared_ptr<T>>;


template <typename T>
bool IsIdentifierDefined(const std::string& id, const IDMapping<T>& where)
{
	return where.find(id) != where.end();
}

template <typename T>
void ThrowIfDefined(const std::string& id, const IDMapping<T>& where)
{
	if (IsIdentifierDefined(id, where))
	{
		throw std::exception("Identifier is already defined");
	}
}

template <typename T>
void ThrowIfNotDefined(const std::string& id, const IDMapping<T>& where)
{
	if (!IsIdentifierDefined(id, where))
	{
		throw std::exception("Identifier is not defined");
	}
}

const std::regex IDENTIFIER_REGEX(R"(^[_A-Za-z]\w*$)");

bool IsIdentifierValid(const std::string& id)
{
	return std::regex_match(id, IDENTIFIER_REGEX);
}

void ThrowIfNotValid(const std::string& id)
{
	if (!IsIdentifierValid(id))
	{
		throw std::exception("Identifier is not valid");
	}
}

} // namespace

double CCalculator::GetValue(const std::string& id) const
{
	ThrowIfNotDefined(id);

	return m_identifiers.at(id)->GetValue();
}

void CCalculator::Var(const std::string& id)
{
	ThrowIfNotValid(id);
	ThrowIfDefined(id);

	auto variable = CVariable::New();
	m_identifiers[id] = variable;
	m_variables[id] = variable;
}

void CCalculator::Let(const std::string& id, double value)
{
	if (!::IsIdentifierDefined(id, m_variables))
	{
		Var(id);
	}

	m_variables.at(id)->SetValue(value);
}

void CCalculator::Let(const std::string& id1, const std::string& id2)
{
	::ThrowIfNotDefined(id2, m_variables);

	double value = GetValue(id2);
	Let(id1, value);
}

void CCalculator::Func(const std::string& fnID, const std::string& id)
{
	ThrowIfNotValid(fnID);
	ThrowIfDefined(fnID);
	ThrowIfNotDefined(id);

	auto function = CFunction::New(m_identifiers.at(id));
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

	auto function = CFunction::New(m_identifiers.at(id1), op, m_identifiers.at(id2));
	m_identifiers[fnID] = function;
	m_functions[fnID] = function;
}
bool CCalculator::IsIdentifierDefined(const std::string& id) const
{
	return ::IsIdentifierDefined(id, m_identifiers);
}

void CCalculator::ThrowIfDefined(const std::string& id) const
{
	::ThrowIfDefined(id, m_identifiers);
}


void CCalculator::ThrowIfNotDefined(const std::string& id) const
{
	::ThrowIfNotDefined(id, m_identifiers);
}
