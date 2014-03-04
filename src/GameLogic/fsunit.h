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
	void Update();

	void Attack(Ptr<FSUnit> pVictim);

	int GetAttack();
	int GetLife();

	void ChangeLife(int nLife);

private:
	FSPropertyAttr m_PropAttr;
	FSPropertyBuff m_PropBuff;
	FSPropertyAbil m_PropAbil;

};
