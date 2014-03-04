#include "stdlogic.h"
#include "fsunit.h"
#include "fsunit_manager.h"

FSUnit::FSUnit(void)
{
}

FSUnit::~FSUnit(void)
{
}

void FSUnit::Update(void)
{
}

void FSUnit::Attack(Ptr<FSUnit> pVictim)
{
	if (!pVictim)
	{
		return;
	}

	int attack1 = this->GetAttack();
	int attack2 = pVictim->GetAttack();
	
	this->ChangeLife(-attack2);
	pVictim->ChangeLife(-attack1);

	FSUnitManager::Instance().UpdateDeadUnit(pVictim);
	FSUnitManager::Instance().UpdateDeadUnit(Ptr<FSUnit>(this));
}

int FSUnit::GetAttack()
{
	return m_PropAttr.m_nAttack;
}

int FSUnit::GetLife()
{
	return m_PropAttr.m_nLife;
}

void FSUnit::ChangeLife(int nLife)
{
	m_PropAttr.m_nLife += nLife;
	if (m_PropAttr.m_nLife + nLife <= 0)
	{
		m_PropAttr.m_nLife = 0;
	}
}

