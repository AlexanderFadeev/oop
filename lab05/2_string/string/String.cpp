#include "String.hpp"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstring>

namespace
{

template <typename T>
T CeilPowerOf2(T value)
{
	return T(1) << std::lround(std::ceil(std::log2(value)));
}

bool IsSeparator(int ch)
{
	return std::isspace(ch) || ch == EOF;
}

} // namespace

CString::CString()
	: CString(nullptr, 0)
{
}

CString::CString(const char* pString)
	: CString(pString, pString ? std::strlen(pString) : 0)
{
} 

CString::CString(const char* pString, size_t length)
	: m_pData(nullptr)
	, m_capacity(0)
{
	if (!pString)
	{
		Resize(1);
		return;
	}

	Resize(length + 1);
	std::memcpy(m_pData, pString, m_size);
}

CString::CString(const CString& other)
	: CString(other.GetData(), other.GetLength())
{
}

CString::CString(CString&& other)
	: CString()
{
	*this = std::move(other);
}

CString::CString(const std::string& stlString)
	: CString(stlString.c_str(), stlString.size())
{
}

CString::~CString()
{
	delete[] m_pData;
}

CString& CString::operator=(const CString& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Resize(rhs.GetLength() + 1);
	std::memcpy(m_pData, rhs.GetData(), rhs.GetLength());
	return *this;
}

CString& CString::operator=(CString&& rhs)
{
	std::swap(m_pData, rhs.m_pData);
	std::swap(m_size, rhs.m_size);
	std::swap(m_capacity, rhs.m_capacity);
	return *this;
}

CString& CString::operator+=(const CString& rhs)
{
	auto newSize = m_size + rhs.GetLength();
	ReserveAtLeast(newSize);
	std::memcpy(m_pData + m_size - 1, rhs.GetData(), rhs.GetLength());
	m_size = newSize;
	m_pData[m_size - 1] = '\0';
	return *this;
}

char& CString::operator[](size_t index)
{
	return m_pData[index];
}

const char& CString::operator[](size_t index) const
{
	return m_pData[index];
}

const CString operator+(CString lhs, const CString& rhs)
{
	return lhs += rhs;
}

bool operator==(const CString& lhs, const CString& rhs)
{
	if (lhs.GetLength() != rhs.GetLength())
	{
		return false;
	}

	auto len = lhs.GetLength();

	for (size_t index = 0; index < len; index++)
	{
		if (lhs[index] != rhs[index])
		{
			return false;
		}
	}

	return true;
}

bool operator!=(const CString& lhs, const CString& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const CString& lhs, const CString& rhs)
{
	auto minLen = std::min(lhs.GetLength(), rhs.GetLength());

	for (size_t index = 0; index < minLen; index++)
	{
		if (lhs[index] < rhs[index])
		{
			return true;
		}
		if (lhs[index] > rhs[index])
		{
			return false;
		}
	}

	return lhs.GetLength() < rhs.GetLength();
}

bool operator>(const CString& lhs, const CString& rhs)
{
	return rhs < lhs;
}

bool operator<=(const CString& lhs, const CString& rhs)
{
	return !(lhs > rhs);
}

bool operator>=(const CString& lhs, const CString& rhs)
{
	return !(lhs < rhs);
}

std::istream& operator>>(std::istream& is, CString& str)
{
	is >> std::ws;

	char ch;
	while (is.get(ch))
	{
		if (IsSeparator(ch))
		{
			is.unget();
			break;
		}

		str.PushBack(ch);
	}

	return is;
}

std::ostream& operator<<(std::ostream& os, const CString& str)
{
	for (size_t index = 0; index < str.m_size; index++)
	{
		os << str.m_pData[index];
	}

	return os;
}

void CString::Clear()
{
	Resize(1);
}

void CString::PushBack(char ch)
{
	ReserveAtLeast(m_size + 1);
	m_size++;
	m_pData[m_size - 1] = '\0';
	m_pData[m_size - 2] = ch;
}

size_t CString::GetLength() const
{
	return m_size - 1;
}

const char* CString::GetData() const
{
	return m_pData;
}

CString CString::SubString(size_t start, size_t length) const
{
	start = std::min(start, m_size);
	length = std::min(length, m_size - 1 - start);
	return CString(m_pData + start, length);
}

void CString::Resize(size_t size)
{
	Reserve(size);
	m_pData[size - 1] = '\0';
	m_size = size;
}

void CString::Reserve(size_t capacity)
{
	if (m_capacity >= capacity)
	{
		return;
	}

	auto newPData = new char[capacity];

	if (m_pData)
	{
		std::memcpy(newPData, m_pData, std::min(m_size, capacity));
		delete[] m_pData;
	}

	m_pData = newPData;
	m_capacity = capacity;
}

void CString::ReserveAtLeast(size_t capacity)
{
	Reserve(CeilPowerOf2(capacity));
}
