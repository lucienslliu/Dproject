#pragma once

#include "fsbase_type.h"
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
	PLAYSEQUENCE player;
	ID attackerID;
	ID victimID;

};

class FSFinishRoundMsg : public FSAsyncMessage
{
	DeclareMsgId

private:
};

/*
enum l2d_Message
{
	l2d_Begin,
	l2d_GameStart = l2d_Begin,
	l2d_DoChange,
	l2d_DoAction,
	l2d_GameEnd,
};
struct dMessage : public Message
{
	d2l_Message msgType;
};


struct dGetReadyMsg : public dMessage
{
	PlayerInfo player[PLAYSEQUENCE_COUNT];

	dGetReadyMsg::dGetReadyMsg()
	{
		msgType = d2l_GetReady;
	}
};

struct dRoundActionMsg : public dMessage
{
	dRoundActionMsg::dRoundActionMsg()
	{
		msgType = d2l_ReqRoundAction;
	}
};

struct dFinishActionMsg : public dMessage
{
	dFinishActionMsg::dFinishActionMsg()
	{
		msgType = d2l_ReqFinishAction;
	}
};


struct dSurranderMsg : public dMessage
{
	dSurranderMsg::dSurranderMsg()
	{
		msgType = d2l_ReqSurrander;
	}
};

//-----------------------------------------------------
struct lMessage : public Message
{
	l2d_Message msgType;
};
*/