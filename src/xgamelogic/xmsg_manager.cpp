#include "stdlogic.h"
#include "xmsg_manager.h"

XMsgManager::XMsgManager(void)
{
}

XMsgManager::~XMsgManager(void)
{
}

void XMsgManager::Init()
{
	m_GameManager.reset(new XGameManager());
	m_GameManager->Initialize();

	this->AttachPort(m_GameManager);
}

void XMsgManager::SendMessage(Message* msg)
{
	Ptr<Message> m(msg);
	Dispatcher::HandleMessage(m);
}

void XMsgManager::SendSyncMessage(Ptr<Message> msg)
{
	Dispatcher::HandleMessage(msg);
}

void XMsgManager::SendAsyncMessage(Ptr<Message> msg)
{
	// 异步消息处理
	// 先按同步来
	m_MsgRB.Push(msg);
}

void XMsgManager::Tick()
{
	Ptr<Message> msg = m_MsgRB.Pop();
	while (msg != NULL)
	{
		SendSyncMessage(msg);
		msg = m_MsgRB.Pop();
	}
}
