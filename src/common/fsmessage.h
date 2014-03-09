#pragma once

#include "base_type.h"
#include "message.h"

//////////////////////////////////////////////////////////////////////////

class FSMessage : public Message
{
	DeclareMsgId
public:

	bool IsSyncMsg() { return m_sync; }
	void SetSyncMsg(bool sync) { m_sync = sync; } 

protected:
	bool m_sync;
};

class FSSyncMessage : public FSMessage
{
	DeclareMsgId
public:
	FSSyncMessage()
	{
		m_sync = true;
	}
};

class FSAsyncMessage : public FSMessage
{
	DeclareMsgId
public:
	FSAsyncMessage()
		: m_playerId(0)
	{
		m_sync = false;
	}

	void SetPlayerID(ID pid) { m_playerId = pid; }
	ID GetPlayerID() { return m_playerId; }

private:
	ID m_playerId;
};

//////////////////////////////////////////////////////////////////////////

struct PlayerInfo 
{
	HERO_PROFESSION profession;
	int cards[CARDS_TOTALNUM];
};

class FSGetReadyMsg : public FSAsyncMessage
{
	DeclareMsgId

public:
	FSGetReadyMsg()
	{
		player.profession = HERO_PROFESSION_1;
		memset(player.cards, 0, sizeof(player.cards));
	}

	PlayerInfo player;
};

class FSUseCardMsg : public FSAsyncMessage
{
	DeclareMsgId

public:
	
	CARD_ID cardID;
};

class FSAttackMsg : public FSAsyncMessage
{
	DeclareMsgId

public:

	ID attackerID;
	ID victimID;

};

class FSUnitDeadMsg : public FSAsyncMessage
{
	DeclareMsgId

public:
	ID attackerID;
	ID victimID;

};

class FSFinishRoundMsg : public FSAsyncMessage
{
	DeclareMsgId
};

class FSSurranderMsg : public FSAsyncMessage
{
	DeclareMsgId
};
