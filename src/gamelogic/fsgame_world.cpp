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
	m_dispatcher.AttachPort(m_GameManager);
}
