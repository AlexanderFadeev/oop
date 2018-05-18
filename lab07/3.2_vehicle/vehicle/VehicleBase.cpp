#include "VehicleBase.hpp"

CVehicleBase::CVehicleBase(size_t seatsCount)
	: m_seatsCount(seatsCount)
{
}

bool CVehicleBase::IsEmpty() const
{
	return GetPassengersCount() == 0;
}

bool CVehicleBase::IsFull() const
{
	return GetPassengersCount() == m_seatsCount;
}

size_t CVehicleBase::GetSeatsCount() const
{
	return m_seatsCount;
}
