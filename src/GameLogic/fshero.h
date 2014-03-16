#pragma once

#include "fsunit.h"

#define MAX_OWNER_UNIT 6

struct UnitSlot 
{
	bool used;
	ID UnitID;
};

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

	void UseCard(CARD_ID card, PLAYSEQUENCE player);

	void KillUnit(ID unitID);

	void FillCrystle();

private:
	int GetEmptySlot();

private:
	int m_nPlayerID;

	HERO_PROFESSION m_Profession;

	typedef std::vector<CARD_ID> CARDLIST;

	CARDLIST m_restCards;
	CARDLIST m_handCards;

	UnitSlot m_UnitList[MAX_OWNER_UNIT];

	int m_nMaxCrystle;
	int m_nCurCrystle;
};
