#pragma once

#include "igame_core.h"
#include "fsgame_thread.h"

class FSGameCore : public IGameCore
{
public:
	FSGameCore(void);
	~FSGameCore(void);

public:
	virtual bool Initialize();

	virtual bool UnInit();

	virtual void SendMessage(Ptr<Message> msg);

private:
	FSGameThread m_GT;
};
