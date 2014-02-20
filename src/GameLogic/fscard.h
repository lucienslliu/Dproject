#pragma once

#include "fsgame_object.h"

class FSCard : public FSGameObject
{
public:
	FSCard(void);
	virtual ~FSCard(void);

private:
	IID m_cardID;
};
