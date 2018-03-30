#pragma once

#include <memory>
#include <vector>

class CIdentifier
	: public std::enable_shared_from_this<CIdentifier>
{
public:
	double GetValue() const;

protected:
	void Expire() const;
	void Uses(std::weak_ptr<const CIdentifier> id) const;
	virtual void InitRelationsImpl() const = 0;
	virtual double CalcValue() const = 0;

private:
	mutable std::vector<std::weak_ptr<const CIdentifier>> m_usesIDs;
	mutable std::vector<std::weak_ptr<const CIdentifier>> m_usedInIDs;

	mutable bool m_isActual = false;
	mutable bool m_relationsInitialized = false;
	mutable double m_value;

	void InitRelations() const;
	void Update() const;
};
