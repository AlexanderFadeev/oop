#include "VehicleBase.hpp"

CVehicleBase::CVehicleBase(size_t seatsCount)
	: m_seatsCount(seatsCount)
	, m_passengersCount(0)
{
}

bool CVehicleBase::IsEmpty() const
{
	return m_passengersCount == 0;
}

bool CVehicleBase::IsFull() const
{
	return m_passengersCount == m_seatsCount;
}

size_t CVehicleBase::GetSeatsCount() const
{
	return m_seatsCount;
}

size_t CVehicleBase::GetPassengersCount() const
{
	return m_passengersCount;
}
