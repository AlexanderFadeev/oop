#pragma once

#include "IPerson.hpp"
#include <string>

template <typename IPerson>
class CPersonImpl
	: public IPerson
{
public:
	CPersonImpl(const std::string& name);

	virtual std::string GetName() const override;
	
private:
	std::string m_name;
};

#include "PersonImpl.ipp"