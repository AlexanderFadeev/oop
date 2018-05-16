#include "IPerson.hpp"

std::ostream& operator<<(std::ostream& os, const IPerson& person)
{
	os << person.GetName();

	return os;
}