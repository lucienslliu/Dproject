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
	this->AttachPort(m_GameManager);
}
