#include "stdlogic.h"
#include "fsgame_world.h"

FSGameWorld::FSGameWorld(void)
{
}

FSGameWorld::~FSGameWorld(void)
{
}

void FSGameWorld::Initialize()
{
}

void FSGameWorld::Tick()
{
	m_GameManager->Tick();
	//Dispatcher::HandleMessage();
}

void FSGameWorld::HandleMessage(const Ptr<Message>& msg)
{
	
}