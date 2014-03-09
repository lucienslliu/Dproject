#include "stdlogic.h"
#include "fsgame_core.h"
#include "fsmsg_manager.h"

FSGameCore::FSGameCore(void)
{
}

FSGameCore::~FSGameCore(void)
{
}

bool FSGameCore::Initialize()
{
	m_GT.Start();
	return true;
}

bool FSGameCore::UnInit()
{
	m_GT.Stop();
	return true;
}

void FSGameCore::SendMessage(Ptr<Message> msg)
{
	FSMsgManager::Instance().SendAsyncMessage(msg);
}

IGameCore* CreateGameCore()
{
	FSGameCore* pCore = new FSGameCore();
	return pCore;
}
