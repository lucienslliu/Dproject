#include "stdlogic.h"
#include "fsgame_manager.h"
#include "fsunit_manager.h"

FSGameManager::FSGameManager(void)
: m_nStep(0)
{
}

FSGameManager::~FSGameManager(void)
{
}

void FSGameManager::Initialize()
{
	RegisterMessage(FSGetReadyMsg::Id);
	RegisterMessage(FSUseCardMsg::Id);
	RegisterMessage(FSAttackMsg::Id);

	FSUnitManager::Instance().Init();

	m_stat = EGameState_WaitPlayer;
	m_nStep = 0;
	m_CurPlayer = PLAYSEQUENCE_FIRST;
}

void FSGameManager::HandleMessage(const Ptr<Message>& msg)
{
	if (!msg)
	{
		return;
	}
	
	ID msgID = msg->GetId();
	if (msgID == FSGetReadyMsg::Id && 
		m_stat == EGameState_WaitPlayer)
	{
		DoGetReady(msg);
	}
	else if (msgID == FSUseCardMsg::Id && 
		m_stat == EGameState_Playing)
	{
		DoUseCard(msg);
	}
	else if (msgID == FSAttackMsg::Id && 
		m_stat == EGameState_Playing)
	{
		DoAttack(msg);
	}
	else
	{
		;
	}
}

void FSGameManager::Tick()
{

}

void FSGameManager::DoGetReady(const Ptr<Message>& msg)
{	
	Ptr<FSGetReadyMsg> getReadyMsg = boost::static_pointer_cast<FSGetReadyMsg>(msg);

	if (m_CurPlayer == PLAYSEQUENCE_FIRST)
	{
		m_Heros[PLAYSEQUENCE_FIRST].SetPlayerID(getReadyMsg->GetPlayerID());
		m_Heros[PLAYSEQUENCE_FIRST].SetProfession(getReadyMsg->player.profession);
		m_Heros[PLAYSEQUENCE_FIRST].SetCards(getReadyMsg->player.cards);
		m_CurPlayer = PLAYSEQUENCE_SECOND;
	}
	else
	{
		m_Heros[PLAYSEQUENCE_SECOND].SetPlayerID(getReadyMsg->GetPlayerID());
		m_Heros[PLAYSEQUENCE_SECOND].SetProfession(getReadyMsg->player.profession);
		m_Heros[PLAYSEQUENCE_SECOND].SetCards(getReadyMsg->player.cards);

		m_stat = EGameState_Playing;
	}

	if (m_stat == EGameState_Playing)
	{
		GameBegin();
	}	
}

void FSGameManager::DoUseCard(const Ptr<Message>& msg)
{
	Ptr<FSUseCardMsg> useCardMsg = boost::static_pointer_cast<FSUseCardMsg>(msg);

	if (m_Heros[m_CurPlayer].GetPlayerID() != useCardMsg->GetPlayerID())
	{
		return;
	}

	m_Heros[m_CurPlayer].UseCard(useCardMsg->cardID);
}

void FSGameManager::GameBegin()
{
	CalcFirstAction();

	const int BEGIN_CARD_NUM = 4;
	const CARD_ID BEGIN_CARD_ID = 1;
	PLAYSEQUENCE otherPlayer = GetOtherPlayer();
	m_Heros[m_CurPlayer].DealCards(BEGIN_CARD_NUM);
	m_Heros[otherPlayer].DealCards(BEGIN_CARD_NUM);
	m_Heros[otherPlayer].DealSpecailCard(BEGIN_CARD_ID);
}

void FSGameManager::CalcFirstAction()
{
	int i = ::rand() % 2;
	if (i > 0)
	{
		m_CurPlayer = PLAYSEQUENCE_FIRST;
	}
	else
	{
		m_CurPlayer = PLAYSEQUENCE_SECOND;
	}
}

PLAYSEQUENCE FSGameManager::GetOtherPlayer()
{
	PLAYSEQUENCE otherPlayer = (m_CurPlayer != PLAYSEQUENCE_SECOND ? PLAYSEQUENCE_SECOND : PLAYSEQUENCE_FIRST);
	return otherPlayer;
}

void FSGameManager::DoChange(const Ptr<Message>& msg)
{
	// 换牌 暂时不搞
}

void FSGameManager::DoAttack(const Ptr<Message>& msg)
{
	// 回合中的操作
	Ptr<FSAttackMsg> getReadyMsg = boost::static_pointer_cast<FSAttackMsg>(msg);

	Ptr<FSUnit> pAttacker = FSUnitManager::Instance().FindUnit(getReadyMsg->attackerID);
	Ptr<FSUnit> pVictim = FSUnitManager::Instance().FindUnit(getReadyMsg->victimID);

	if (!pAttacker || !pVictim)
	{
		return;
	}

	// 攻击
	pAttacker->Attack(pVictim);

}

void FSGameManager::DoFinishAction(const Ptr<Message>& msg)
{
	// 回合结束事件
	SendRoundEndEvent();

	m_CurPlayer = GetOtherPlayer();
	m_Heros[m_CurPlayer].DealOneCard();

	// 回合开始事件
	SendRoundBeginEvent();
}

void FSGameManager::DoSurrander(const Ptr<Message>& msg)
{

}

void FSGameManager::SendRoundBeginEvent()
{

}

void FSGameManager::SendRoundEndEvent()
{

}
