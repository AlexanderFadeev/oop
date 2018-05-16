#pragma once

#include "IVehicleBase.hpp"

class CVehicleBase
	: public virtual IVehicleBase
{
public:
	CVehicleBase(size_t seatsCount);

	virtual bool IsEmpty() const override;
	virtual bool IsFull() const override;
	virtual size_t GetSeatsCount() const override;
	virtual size_t GetPassengersCount() const override;

protected:
	size_t m_passengersCount;

private:
	size_t m_seatsCount;
};

