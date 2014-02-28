#pragma once

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

	void Tick();

	void HandleMessage(const Ptr<Message>& msg);

private:

};
