#pragma once

#include "igame_core.h"
#include "xgame_thread.h"

class XGameCore : public IGameCore
{
public:
	XGameCore(void);
	~XGameCore(void);

public:
	virtual bool Initialize();

	virtual bool UnInit();

	virtual void SendMessage(Ptr<Message> msg);

private:
	XGameThread m_GT;
};
