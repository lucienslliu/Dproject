#pragma once

//-----------------------------------------------------
interface iMessage
{
	const ID& GetID() { return id; }

	static ID id;
};

interface IMsgHandle
{
	virtual void SendMessage() = 0;

};