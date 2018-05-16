#pragma once

#include "Car.hpp"
#include "ITaxi.hpp"
#include "Vehicle.hpp"

class CTaxi
	: public CCar<CVehicle<ITaxi, IPerson>>
{
	using CCar::CCar;
};
