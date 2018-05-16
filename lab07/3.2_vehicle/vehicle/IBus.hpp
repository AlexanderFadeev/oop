#pragma once

#include "IVehicle.hpp"
#include "IPerson.hpp"

class IBus
	: public IVehicle<IPerson>
{
};