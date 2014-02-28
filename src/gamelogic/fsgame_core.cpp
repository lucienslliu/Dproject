#include "stdlogic.h"
#include "fsgame_core.h"

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

void FSGameCore::SendMessage(Message* msg)
{

}

IGameCore* CreateGameCore()
{
	IGameCore* pCore = new FSGameCore();
	return pCore;
}
