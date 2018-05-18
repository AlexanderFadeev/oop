#pragma once

#include "IVehicleBase.hpp"

class CVehicleBase
	: public virtual IVehicleBase
{
public:
	CVehicleBase(size_t seatsCount);

	bool IsEmpty() const override;
	bool IsFull() const override;
	size_t GetSeatsCount() const override;
	size_t GetPassengersCount() const override;

protected:
	size_t m_passengersCount;

private:
	size_t m_seatsCount;
};

