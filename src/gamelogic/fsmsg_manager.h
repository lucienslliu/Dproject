#pragma once

#include "ringbuffer.h"
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

	void SendSyncMessage(Ptr<Message> msg);

	void SendAsyncMessage(Ptr<Message> msg);

	void Tick();

private:
	Ptr<FSGameManager> m_GameManager;

	MsgRingBuffer m_MsgRB;
};
