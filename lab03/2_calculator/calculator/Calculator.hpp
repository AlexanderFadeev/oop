#pragma once

#include "Function.hpp"
#include "Identifier.hpp"
#include "Variable.hpp"
#include <map>
#include <memory>
#include <regex>
#include <string>

class CCalculator
{
public:
	double GetValue(const std::string& id) const;
	void Var(const std::string& id);
	void Let(const std::string& id, double value);
	void Let(const std::string& id1, const std::string& id2);
	void Func(const std::string& fnID, const std::string& id);
	void Func(const std::string& fnID, const std::string& id1, CFunction::Operator op, const std::string& id2);

private:
	static const std::regex m_identifierRegex;

	template <typename T>
	using IDMapping = std::map<std::string, std::shared_ptr<T>>;

	IDMapping<CIdentifier> m_identifiers;
	IDMapping<CVariable> m_variables;
	IDMapping<CFunction> m_functions;

	template <typename T>
	bool IsIdentifierDefined(const std::string& id, const IDMapping<T>& where) const;
	template <typename T>
	void ThrowIfDefined(const std::string& id, const IDMapping<T>& where) const;
	template <typename T>
	void ThrowIfNotDefined(const std::string& id, const IDMapping<T>& where) const;

	void ThrowIfNotValid(const std::string& id) const;
	bool IsIdentifierValid(const std::string& id) const;
	bool IsIdentifierDefined(const std::string& id) const;
	void ThrowIfDefined(const std::string& id) const;
	void ThrowIfNotDefined(const std::string& id) const;
};
