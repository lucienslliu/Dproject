#pragma once

#include "dispatcher.h"
#include "fsgame_manager.h"

class FSGameWorld : public Dispatcher
{
public:
	FSGameWorld(void);
	~FSGameWorld(void);

	static FSGameWorld& Instance()
	{
		static FSGameWorld GW;
		return GW;
	}

public:
	void Initialize();

	void Run();

private:
	Ptr<FSGameManager> m_GameManager;

};
