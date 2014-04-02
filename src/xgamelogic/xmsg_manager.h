#pragma once

#include "ringbuffer.h"
#include "dispatcher.h"
#include "fsmessage.h"
#include "xgame_manager.h"

class XMsgManager : public Dispatcher
{
public:
	XMsgManager(void);
	~XMsgManager(void);

	static XMsgManager& Instance()
	{
		static XMsgManager FSMM;
		return FSMM;
	}

public:
	void Init();

	void SendMessage(Message* msg);

	void SendSyncMessage(Ptr<Message> msg);

	void SendAsyncMessage(Ptr<Message> msg);

	void Tick();

private:
	Ptr<XGameManager> m_GameManager;

	MsgRingBuffer m_MsgRB;
};
