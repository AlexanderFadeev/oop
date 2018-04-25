#pragma once

#include <memory>
#include <optional>
#include <vector>

class CIdentifier
	: public std::enable_shared_from_this<CIdentifier>
{
public:
	using WeakPtr = std::weak_ptr<CIdentifier>;

	virtual ~CIdentifier() = default;

	double GetValue() const;

protected:
	void Uses(const WeakPtr& id);
	void Expire() const;

private:
	using WeakConstPtr = std::weak_ptr<CIdentifier>;
	using WeakConstPtrVec = std::vector<WeakConstPtr>;

	virtual double CalcValue() const = 0;
	void Update() const;

	WeakConstPtrVec m_usesIDs;
	WeakConstPtrVec m_usedInIDs;

	mutable std::optional<double> m_value = std::nullopt;
};
