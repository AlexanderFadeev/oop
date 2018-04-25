#pragma once

#include <memory>
#include <optional>
#include <vector>

class CIdentifier
	: public std::enable_shared_from_this<CIdentifier>
{
public:
	virtual ~CIdentifier() = default;

	double GetValue() const;

protected:
	void Uses(std::weak_ptr<CIdentifier> id);
	void Expire() const;

private:
	using WeakPtr = std::weak_ptr<const CIdentifier>;
	using WeakPtrVec = std::vector<WeakPtr>;

	virtual double CalcValue() const = 0;
	void Update() const;

	WeakPtrVec m_usesIDs;
	WeakPtrVec m_usedInIDs;

	mutable std::optional<double> m_value = std::nullopt;
};
