#pragma once

#include "fsmessage.h"
#include "fshero.h"
#include "port.h"

class FSGameManager : public Port
{
public:
	FSGameManager(void);
	~FSGameManager(void);

public:
	void Initialize();

	void HandleMessage(dMessage* msg);

private:
	void DoGetReady(dMessage* msg);
	void DoChange(dMessage* msg);
	void DoRoundAction(dMessage* msg);
	void DoFinishAction(dMessage* msg);
	void DoSurrander(dMessage* msg);

private:
	void CalcFirstAction();

	PLAYSEQUENCE GetOtherPlayer();

private:
	// ·¢ËÍÊÂ¼þ
	void SendRoundBeginEvent();

	void SendRoundEndEvent();

private:

	int m_nStep;

	FSHero m_Heros[PLAYSEQUENCE_COUNT];

	PLAYSEQUENCE m_CurPlayer;
};
