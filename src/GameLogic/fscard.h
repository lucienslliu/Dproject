#pragma once

#include "fsgame_object.h"

#define MAX_CARD_NUM 100

class FSCard : public FSGameObject
{
public:
	FSCard(void);
	virtual ~FSCard(void);

	static int GetCardCost(CARD_ID cardID);

private:
	ID m_cardID;

	int m_nSpend;

	static int ms_CardCost[MAX_CARD_NUM];
};
