#pragma once

#include "IRacer.hpp"
#include "PersonImpl.hpp"

class CRacer
	: public CPersonImpl<IRacer>
{
	using CPersonImpl::CPersonImpl;
};