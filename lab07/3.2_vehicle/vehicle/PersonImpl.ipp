#pragma once

#include "PersonImpl.hpp"

template<typename P>
inline CPersonImpl<P>::CPersonImpl(const std::string& name)
	: m_name(name)
{
}

template<typename P>
inline std::string CPersonImpl<P>::GetName() const
{
	return m_name;
}
