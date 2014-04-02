#include "stdlogic.h"
#include "xgame_manager.h"

XGameManager::XGameManager(void)
: m_nStep(0)
{
}

XGameManager::~XGameManager(void)
{
}

void XGameManager::Initialize()
{
// 	RegisterMessage(FSGetReadyMsg::Id);
// 	RegisterMessage(FSUseCardMsg::Id);
// 	RegisterMessage(FSAttackMsg::Id);
// 	RegisterMessage(FSUnitDeadMsg::Id);
// 	RegisterMessage(FSFinishRoundMsg::Id);
// 	RegisterMessage(FSSurranderMsg::Id);

	m_stat = EGameState_WaitPlayer;
	m_nStep = 0;
	m_CurPlayer = PLAYSEQUENCE_FIRST;
}

void XGameManager::HandleMessage(const Ptr<Message>& msg)
{
	if (!msg)
	{
		return;
	}
	
	ID msgID = msg->GetId();
// 	if (m_stat == EGameState_WaitPlayer && msgID == FSGetReadyMsg::Id)
// 	{
// 		DoGetReady(msg);
// 	}
// 	else if (m_stat == EGameState_Playing)
// 	{
// 		if (msgID == FSUseCardMsg::Id)
// 		{
// 			DoUseCard(msg);
// 		}
// 		else if (msgID == FSAttackMsg::Id)
// 		{
// 			DoAttack(msg);
// 		}
// 		else if (msgID == FSUnitDeadMsg::Id)
// 		{
// 			DoUnitDead(msg);
// 		}
// 		else if (msgID == FSFinishRoundMsg::Id)
// 		{
// 			DoFinishRound(msg);
// 		}
// 	}
// 	else
// 	{
// 		;
// 	}
}

void XGameManager::Tick()
{

}

void XGameManager::DoGetReady(const Ptr<Message>& msg)
{	
	Ptr<FSGetReadyMsg> getReadyMsg = boost::static_pointer_cast<FSGetReadyMsg>(msg);

	if (m_CurPlayer == PLAYSEQUENCE_FIRST)
	{
		m_CurPlayer = PLAYSEQUENCE_SECOND;
	}
	else
	{

		m_stat = EGameState_Playing;
	}

	if (m_stat == EGameState_Playing)
	{
		GameBegin();
	}
}

void XGameManager::DoUseCard(const Ptr<Message>& msg)
{
}

void XGameManager::GameBegin()
{
	CalcFirstAction();

	const int BEGIN_CARD_NUM = 4;
	const CARD_ID BEGIN_CARD_ID = 1;
	PLAYSEQUENCE otherPlayer = GetOtherPlayer();
}

void XGameManager::CalcFirstAction()
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

PLAYSEQUENCE XGameManager::GetOtherPlayer()
{
	PLAYSEQUENCE otherPlayer = (m_CurPlayer != PLAYSEQUENCE_SECOND ? PLAYSEQUENCE_SECOND : PLAYSEQUENCE_FIRST);
	return otherPlayer;
}

void XGameManager::DoChange(const Ptr<Message>& msg)
{
	// 换牌 暂时不搞
	msg;
}

void XGameManager::DoAttack(const Ptr<Message>& msg)
{
}

void XGameManager::DoUnitDead(const Ptr<Message>& msg)
{
}

void XGameManager::DoFinishRound(const Ptr<Message>& msg)
{

	// 回合结束事件
	SendRoundEndEvent();

	m_CurPlayer = GetOtherPlayer();

	// 回合开始事件
	SendRoundBeginEvent();
}

void XGameManager::DoSurrander(const Ptr<Message>& msg)
{
}

void XGameManager::SendRoundBeginEvent()
{

}

void XGameManager::SendRoundEndEvent()
{

}

void XGameManager::GameOver(ID loser)
{
	loser;
}