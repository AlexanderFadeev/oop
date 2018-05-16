#pragma once

#include "IPerson.hpp"

class IPoliceMan
	: public IPerson
{
public:
	virtual std::string GetDepartamentName() const = 0;
};

std::ostream& operator<<(std::ostream& os, const IPoliceMan& policeMan);