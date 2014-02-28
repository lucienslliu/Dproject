#include "stdlogic.h"
#include "fsunit_manager.h"

FSUnitManager::FSUnitManager(void)
{
}

FSUnitManager::~FSUnitManager(void)
{
}

FSUnit* FSUnitManager::CreateUnit()
{
	FSUnit* unit = new FSUnit();

	m_unitmap[unit->GetUniqueID()] = unit;

	return unit;
}

void FSUnitManager::DestroyUnit(FSUnit* unit)
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
