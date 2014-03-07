#pragma once

#include "fsmessage.h"
#include "fshero.h"
#include "port.h"

enum EGameState
{
	EGameState_WaitPlayer,
	EGameState_Playing,
	EGameState_Finish,
};

class FSGameManager : public Port
{
public:
	FSGameManager(void);
	~FSGameManager(void);

public:
	void Initialize();

	void HandleMessage(const Ptr<Message>& msg);

	void Tick();

private:
	void DoGetReady(const Ptr<Message>& msg);
	void DoUseCard(const Ptr<Message>& msg);
	void DoChange(const Ptr<Message>& msg);
	void DoAttack(const Ptr<Message>& msg);
	void DoUnitDead(const Ptr<Message>& msg);
	void DoFinishRound(const Ptr<Message>& msg);
	void DoSurrander(const Ptr<Message>& msg);

private:
	void GameBegin();

	void CalcFirstAction();

	PLAYSEQUENCE GetOtherPlayer();


private:
	// ·¢ËÍÊÂ¼þ
	void SendRoundBeginEvent();

	void SendRoundEndEvent();

private:
	EGameState m_stat;

	int m_nStep;

	FSHero m_Heros[PLAYSEQUENCE_COUNT];

	PLAYSEQUENCE m_CurPlayer;
};
