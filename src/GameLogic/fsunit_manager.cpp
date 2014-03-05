#include "stdlogic.h"
#include "fsunit_manager.h"

struct UnitProp
{
	int nLife;
	int nAttack;
};

UnitProp UnitProps[] = 
{
	{ 5, 5 },
};

FSUnitManager::FSUnitManager(void)
{
}

FSUnitManager::~FSUnitManager(void)
{
}

bool FSUnitManager::Init()
{
	return true;
}

Ptr<FSUnit> FSUnitManager::CreateUnit(ID unitID)
{
	Ptr<FSUnit> unit(new FSUnit());
	m_unitmap[unit->GetUniqueID()] = unit;
	
	unit->SetLife(UnitProps[unitID].nLife);
	unit->SetAttack(UnitProps[unitID].nAttack);

	return unit;
}

void FSUnitManager::DestroyUnit(Ptr<FSUnit> unit)
{
	if (unit)
	{
		DestroyUnit(unit->GetUniqueID());
	}
}

void FSUnitManager::DestroyUnit(ID unitID)
{
	UNITMAP::iterator it = m_unitmap.find(unitID);
	if (it != m_unitmap.end())
	{
		m_unitmap.erase(it);
	}
}

void FSUnitManager::Update()
{
	UNITMAP::iterator it = m_unitmap.begin();
	for (; it != m_unitmap.end(); it++)
	{
		it->second->Update();
	}
}

Ptr<FSUnit> FSUnitManager::FindUnit(ID unitID)
{
	Ptr<FSUnit> unit;
	UNITMAP::iterator it = m_unitmap.find(unitID);
	if (it != m_unitmap.end())
	{
		unit = it->second;
		return unit;
	}

	return unit;
}


void FSUnitManager::UpdateDeadUnit(Ptr<FSUnit> unit)
{
	if (!unit)
	{
		return;
	}

	if (unit->GetLife() <= 0)
	{
		FSUnitManager::Instance().DestroyUnit(unit);
	}
}

