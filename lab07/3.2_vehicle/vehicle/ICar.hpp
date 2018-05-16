#pragma once

#include "CarBrand.h"
#include "IVehicle.hpp"

template <typename IPassenger>
class ICar
	: public IVehicle<IPassenger>
{
public:
	using Brand = CarBrand;

	virtual Brand GetBrand() const = 0;
};
