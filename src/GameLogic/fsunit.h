#pragma once

#include "stdlogic.h"
#include "fsgame_object.h"
#include "fsproperty_attr.h"
#include "fsproperty_buff.h"
#include "fsproperty_abil.h"

class FSUnit : public FSGameObject
{
public:
	FSUnit(void);
	virtual ~FSUnit(void);

public:
	void SetPlayer(PLAYSEQUENCE player);
	void Update();

	void Attack(Ptr<FSUnit> pVictim);

	int GetAttack();
	int GetLife();

	void SetAttack(int attack);
	void SetLife(int life);

	void ChangeLife(int nLife);

protected:
	FSPropertyAttr m_PropAttr;
	FSPropertyBuff m_PropBuff;
	FSPropertyAbil m_PropAbil;

	PLAYSEQUENCE m_Player;
};
