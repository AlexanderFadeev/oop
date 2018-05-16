#pragma once

#include "Car.hpp"
#include "IPoliceCar.hpp"
#include "Vehicle.hpp"

class CPoliceCar
	: public CCar<CVehicle<IPoliceCar, IPoliceMan>>
{
	using CCar::CCar;
};