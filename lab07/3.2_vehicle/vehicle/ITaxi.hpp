#pragma once

#include "ICar.hpp"
#include "IPerson.hpp"

class ITaxi
	: public ICar<IPerson>
{
};