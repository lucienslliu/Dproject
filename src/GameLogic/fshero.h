#pragma once

#include "fsunit.h"

class FSHero : public FSUnit
{
public:
	FSHero(void);
	virtual ~FSHero(void);

public:
	HERO_PROFESSION GetProfession() { return m_Profession; }
	void SetProfession(HERO_PROFESSION prof) { m_Profession = prof; }

	int GetPlayerID() { return m_nPlayerID; }
	void SetPlayerID(int nID) { m_nPlayerID = nID; }

public:
	void SetCards(CARD_ID cards[CARDS_TOTALNUM]);

	void DealCards(int nNum);

	void DealOneCard();

	void DealSpecailCard(CARD_ID card);

private:
	int m_nPlayerID;

	HERO_PROFESSION m_Profession;

	std::vector<CARD_ID> m_restCards;
	std::vector<CARD_ID> m_useCards;
};
