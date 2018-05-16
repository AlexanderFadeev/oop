#pragma once

#include "Car.hpp"
#include "IRacingCar.h"
#include "Vehicle.hpp"

class CRacingCar
	: public CCar<CVehicle<IRacingCar, IRacer>>
{
	using CCar::CCar;
};