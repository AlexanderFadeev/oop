#pragma once

#include "IVehicleBase.hpp"
#include <memory>

template <typename IPassenger>
class IVehicle
	: public virtual IVehicleBase
{
public:
	virtual const IPassenger& GetPassenger(size_t index) const = 0;

	virtual void AddPassenger(std::shared_ptr<IPassenger> pPassenger) = 0;
};