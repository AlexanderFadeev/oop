#pragma once

#include <string>
#include <iostream>

class IPerson
{
public:
	virtual ~IPerson() = default;

	virtual std::string GetName() const = 0;
};

std::ostream& operator<<(std::ostream& os, const IPerson& person);
