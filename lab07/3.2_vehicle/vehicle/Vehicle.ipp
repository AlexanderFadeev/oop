#pragma once

#include "Vehicle.hpp"
#include <stdexcept>

template<typename V, typename P>
inline CVehicle<V, P>::CVehicle(size_t seatsCount)
	: CVehicleBase(seatsCount)
{
}

template<typename V, typename P>
inline const P& CVehicle<V, P>::GetPassenger(size_t index) const
{
	if (index >= m_passengers.size())
	{
		throw std::out_of_range("passenger index is out of range");
	}

	return *m_passengers[index];
}

template<typename V, typename P>
inline void CVehicle<V, P>::AddPassenger(std::shared_ptr<P> pPassenger)
{
	if (IsFull())
	{
		throw std::logic_error("trying to add passenger in full vehicle");
	}

	m_passengers.push_back(std::move(pPassenger));
	m_passengersCount++;
}

template<typename V, typename P>
inline void CVehicle<V, P>::RemovePassenger(size_t index)
{
	if (index >= m_passengers.size())
	{
		throw std::out_of_range("passenger index is out of range");
	}

	auto it = m_passengers.begin() + index;
	m_passengers.erase(it);
	m_passengersCount--;
}

template<typename V, typename P>
inline void CVehicle<V, P>::RemoveAllPassengers()
{
	m_passengers.clear();
	m_passengersCount = 0;
}

#pragma region Fix For Warning 4250: inherits via dominance
template<typename V, typename P>
inline bool CVehicle<V, P>::IsEmpty() const
{
	return CVehicleBase::IsEmpty();
}

template<typename V, typename P>
inline bool CVehicle<V, P>::IsFull() const
{
	return CVehicleBase::IsFull();
}

template<typename V, typename P>
inline size_t CVehicle<V, P>::GetSeatsCount() const
{
	return CVehicleBase::GetSeatsCount();
}

template<typename V, typename P>
inline size_t CVehicle<V, P>::GetPassengersCount() const
{
	return CVehicleBase::GetPassengersCount();
}
#pragma endregion