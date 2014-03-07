#include "stdlogic.h"
#include "fshero.h"
#include "fsunit_manager.h"

FSHero::FSHero(void)
: m_nPlayerID(INVALID_ID)
{
	m_PropAttr.m_nLife = 30;
	m_PropAttr.m_nAttack = 0;
	memset(m_UnitList, 0, sizeof(m_UnitList));
}

FSHero::~FSHero(void)
{

}

void FSHero::SetCards(CARD_ID cards[CARDS_TOTALNUM])
{ 
	for (int i = 0; i < CARDS_TOTALNUM; i++)
	{
		m_restCards.push_back(cards[i]);
	}
}

void FSHero::DealCards(int nNum)
{
	for (int i = 0; i < nNum; i++)
	{
		DealOneCard();
	}
}

void FSHero::DealSpecailCard(CARD_ID card)
{
	m_handCards.push_back(card);
}

void FSHero::UseCard(CARD_ID card, PLAYSEQUENCE player)
{
	int nSlot = GetEmptySlot();
	if (INVALID_INDEX == nSlot)
	{
		return;
	}

	CARDLIST::iterator it = std::find(m_handCards.begin(), m_handCards.end(), card);
	if (it == m_handCards.end())
	{
		return;
	}

	// 创建单位
	Ptr<FSUnit> pUnit = FSUnitManager::Instance().CreateUnit(card);
	if (pUnit)
	{
		pUnit->SetPlayer(player);
		m_UnitList[nSlot].UnitID = pUnit->GetUniqueID();
		m_UnitList[nSlot].used = true;
	}

	m_handCards.erase(it);
}

void FSHero::KillUnit(ID unitID)
{
	for (int i = 0; i < MAX_OWNER_UNIT; i++)
	{
		if (true == m_UnitList[i].used && m_UnitList[i].UnitID == unitID)
		{
			m_UnitList[i].used = false;
			m_UnitList[i].UnitID = 0;
			return;
		}		
	}
}

int FSHero::GetEmptySlot()
{
	for (int i = 0; i < MAX_OWNER_UNIT; i++)
	{
		if (false == m_UnitList[i].used)
		{
			return i;
		}
	}
	return INVALID_INDEX;
}

void FSHero::DealOneCard()
{
	int nNum = m_restCards.size();
	int nIndex = rand() % nNum;

	m_handCards.push_back(m_restCards[nIndex]);
	m_restCards.erase(m_restCards.begin() + nIndex - 1);
}
