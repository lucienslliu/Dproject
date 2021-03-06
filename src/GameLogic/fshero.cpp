#include "stdlogic.h"
#include "fshero.h"
#include "fsunit_manager.h"
#include "fscard.h"

FSHero::FSHero(void)
: m_nPlayerID(INVALID_ID)
, m_nMaxCrystle(1)
, m_nCurCrystle(1)
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

bool FSHero::UseCard(CARD_ID card, PLAYSEQUENCE player)
{
	int nCost = FSCard::GetCardCost(card);
	if (nCost > m_nCurCrystle)
	{
		return false;
	}

	int nSlot = GetEmptySlot();
	if (INVALID_INDEX == nSlot)
	{
		return false;
	}

	CARDLIST::iterator it = std::find(m_handCards.begin(), m_handCards.end(), card);
	if (it == m_handCards.end())
	{
		return false;
	}

	// ������λ
	Ptr<FSUnit> pUnit = FSUnitManager::Instance().CreateUnit(card);
	if (pUnit)
	{
		pUnit->SetPlayer(player);
		m_UnitList[nSlot].UnitID = pUnit->GetUniqueID();
		m_UnitList[nSlot].used = true;
	}
	else
	{
		return false;
	}

	m_handCards.erase(it);
	m_nCurCrystle -= nCost;

	return true;
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

void FSHero::FillCrystle()
{
	m_nMaxCrystle++;
	m_nCurCrystle = m_nMaxCrystle;
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
