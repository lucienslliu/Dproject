#pragma once

#include "igame_core.h"

class FSGameCore : public IGameCore
{
public:
	FSGameCore(void);
	~FSGameCore(void);

public:
	virtual bool Initialize();

	virtual void SendMessage();
};
