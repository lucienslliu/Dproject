#pragma once

#include "fsbase_type.h"
#include "imessage.h"
#include "message.h"

class GetReadyMsg : public Message
{
	DeclareMsgId
};

enum d2l_Message
{
	d2l_Begin,
	d2l_GetReady = d2l_Begin,
	d2l_ReqChange,
	d2l_ReqRoundAction,
	d2l_ReqFinishAction,
	d2l_ReqSurrander,
};

enum l2d_Message
{
	l2d_Begin,
	l2d_GameStart = l2d_Begin,
	l2d_DoChange,
	l2d_DoAction,
	l2d_GameEnd,
};

struct dMessage : public iMessage
{
	d2l_Message msgType;
};

struct PlayerInfo 
{
	int nPlayerID;
	HERO_PROFESSION profession;
	int cards[CARDS_TOTALNUM];
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
struct lMessage : public iMessage
{
	l2d_Message msgType;
};
