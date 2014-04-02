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
	Dispatcher::HandleMessage(msg);
}

void FSMsgManager::SendAsyncMessage(Ptr<Message> msg)
{
	// 异步消息处理
	// 先按同步来
	m_MsgRB.Push(msg);
}

void FSMsgManager::Tick()
{
	Ptr<Message> msg = m_MsgRB.Pop();
	while (msg != NULL)
	{
		SendSyncMessage(msg);
		msg = m_MsgRB.Pop();
	}
}
