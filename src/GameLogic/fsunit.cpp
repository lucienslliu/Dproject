#include "stdlogic.h"
#include "fsunit.h"
#include "fsmsg_manager.h"
#include "fsunit_manager.h"
#include "fsgame_manager.h"

FSUnit::FSUnit(void)
{
}

FSUnit::~FSUnit(void)
{
}

void FSUnit::SetPlayer(PLAYSEQUENCE player)
{
	m_Player = player; 
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

	if (pVictim->GetLife() <= 0)
	{
		Ptr<FSUnitDeadMsg> msg(new FSUnitDeadMsg());
		msg->attackerID = this->GetUniqueID(); 
		msg->victimID = pVictim->GetUniqueID();
		FSMsgManager::Instance().SendSyncMessage(msg);
	}

	if (this->GetLife() <= 0)
	{
		Ptr<FSUnitDeadMsg> msg(new FSUnitDeadMsg());
		msg->attackerID = pVictim->GetUniqueID(); 
		msg->victimID = this->GetUniqueID();
		FSMsgManager::Instance().SendSyncMessage(msg);
	}

}

int FSUnit::GetAttack()
{
	return m_PropAttr.m_nAttack;
}

int FSUnit::GetLife()
{
	return m_PropAttr.m_nLife;
}

void FSUnit::SetAttack(int attack)
{
	m_PropAttr.m_nAttack = attack;
}

void FSUnit::SetLife(int life)
{
	m_PropAttr.m_nLife = life;
}

void FSUnit::ChangeLife(int nLife)
{
	m_PropAttr.m_nLife += nLife;
	if (m_PropAttr.m_nLife + nLife <= 0)
	{
		m_PropAttr.m_nLife = 0;
	}
}

