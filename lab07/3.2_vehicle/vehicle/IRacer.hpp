#pragma once

#include "IPerson.hpp"

class IRacer
	: public IPerson
{
	virtual size_t GetAwardsCount() const = 0;
};