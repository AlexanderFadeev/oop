#pragma once

#include "ICar.hpp"
#include "IRacer.hpp"

class IRacingCar
	: public ICar<IRacer>
{
};