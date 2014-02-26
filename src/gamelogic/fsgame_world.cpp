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
	m_GameManager.reset(new FSGameManager());
	m_GameManager->Initialize();

	this->AttachPort(m_GameManager);
}

void FSGameWorld::Run()
{
}