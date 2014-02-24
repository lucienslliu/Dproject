#pragma once

#include "dispatcher.h"
#include "fsgame_manager.h"

class FSGameWorld : public Dispatcher
{
public:
	FSGameWorld(void);
	~FSGameWorld(void);

public:
	void Initialize();

private:
	Ptr<FSGameManager> m_GameManager;

};
