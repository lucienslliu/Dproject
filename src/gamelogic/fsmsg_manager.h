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

	void SendSyncMessage(Ptr<Message> msg);

	void SendAsyncMessage(Ptr<Message> msg);

private:
	Ptr<FSGameManager> m_GameManager;

	typedef std::vector<Ptr<Message> > MESSAGELIST;
	MESSAGELIST m_MsgList;
};
