#pragma once

#include "dispatcher.h"
#include "fsmessage.h"
#include "fsgame_manager.h"

class FSMsgManager : public Dispatcher
{
public:
	FSMsgManager(void);
	~FSMsgManager(void);

	static FSMsgManager& Instance()
	{
		static FSMsgManager FSMM;
		return FSMM;
	}

public:
	void Init();

	void SendMessage(Message* msg);

private:
	Ptr<FSGameManager> m_GameManager;
};
