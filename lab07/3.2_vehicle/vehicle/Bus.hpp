#pragma once

#include "IBus.hpp"
#include "Vehicle.hpp"

class CBus
	: public CVehicle<IBus, IPerson>
{
	using CVehicle::CVehicle;
};