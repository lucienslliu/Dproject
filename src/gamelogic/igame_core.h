#pragma once

class IGameCore
{
public:
	virtual bool Initialize() = 0;
	virtual void SendMessage() = 0;

};

int CreateGameCore()
{
	return 0;
}