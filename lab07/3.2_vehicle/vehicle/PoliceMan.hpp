#pragma once

#include "IPoliceMan.hpp"
#include "PersonImpl.hpp"

class CPoliceMan
	: public CPersonImpl<IPoliceMan>
{
public:
	CPoliceMan(const std::string& name, const std::string& departamentName);

	std::string GetDepartamentName() const override;

private:
	std::string m_departamentName;
};