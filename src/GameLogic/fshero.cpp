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
	m_handCards.push_back(card);
}

void FSHero::UseCard(CARD_ID card)
{
	CARDLIST::iterator it = std::find(m_handCards.begin(), m_handCards.end(), card);
	if (it == m_handCards.end())
	{
		return;
	}

	

	m_handCards.erase(it);
}

void FSHero::DealOneCard()
{
	int nNum = m_restCards.size();
	int nIndex = rand() % nNum;

	m_handCards.push_back(m_restCards[nIndex]);
	m_restCards.erase(m_restCards.begin() + nIndex - 1);
}
