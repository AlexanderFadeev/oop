#pragma once

#include "ICar.hpp"
#include "IPoliceMan.hpp"

class IPoliceCar
	: public ICar<IPoliceMan>
{
};