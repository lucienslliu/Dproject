#include "stdlogic.h"
#include "xgame_core.h"
#include "xmsg_manager.h"

XGameCore::XGameCore(void)
{
}

XGameCore::~XGameCore(void)
{
}

bool XGameCore::Initialize()
{
	m_GT.Start();
	return true;
}

bool XGameCore::UnInit()
{
	m_GT.Stop();
	return true;
}

void XGameCore::SendMessage(Ptr<Message> msg)
{
	XMsgManager::Instance().SendAsyncMessage(msg);
}

IGameCore* CreateGameCore()
{
	XGameCore* pCore = new XGameCore();
	return pCore;
}
