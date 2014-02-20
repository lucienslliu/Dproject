#include "stdlogic.h"
#include "fshero.h"

FSHero::FSHero(void)
: m_nPlayerID(INVALID_ID)
{

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
	m_useCards.push_back(card);
}

void FSHero::DealOneCard()
{
	int nNum = m_restCards.size();
	int nIndex = rand() % nNum;

	m_useCards.push_back(m_restCards[nIndex]);
	m_restCards.erase(m_restCards.begin() + nIndex - 1);
}
