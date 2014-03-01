#include "stdlogic.h"
#include "fsmsg_manager.h"

FSMsgManager::FSMsgManager(void)
{
}

FSMsgManager::~FSMsgManager(void)
{
}

void FSMsgManager::Init()
{
	m_GameManager.reset(new FSGameManager());
	m_GameManager->Initialize();

	this->AttachPort(m_GameManager);
}

void FSMsgManager::SendMessage(Message* msg)
{
	Ptr<Message> m(msg);
	Dispatcher::HandleMessage(m);
}

void FSMsgManager::SendSyncMessage(Ptr<Message> msg)
{
	Ptr<Message> m(msg);
	Dispatcher::HandleMessage(m);
}

void FSMsgManager::SendAsyncMessage(Ptr<Message> msg)
{
	m_MsgList.push_back(msg);
}
