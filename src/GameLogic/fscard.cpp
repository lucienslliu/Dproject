#include "stdlogic.h"
#include "FSCard.h"

int FSCard::ms_CardCost[MAX_CARD_NUM] =
{
	1, 2, 3, 3
};

FSCard::FSCard(void)
: m_cardID(0)
, m_nSpend(0)
{
}

FSCard::~FSCard(void)
{
}

int FSCard::GetCardCost(CARD_ID cardID)
{
	return ms_CardCost[cardID];
}