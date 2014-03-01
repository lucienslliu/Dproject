#include "stdlogic.h"
#include "fsgame_manager.h"
#include <math.h>

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
	/*switch (msgID)
	{
	case Message::CheckId:
		DoGetReady(msg);
		break;
	case d2l_ReqChange:
		DoChange(msg);
		break;
	case d2l_ReqRoundAction:
		DoRoundAction(msg);
		break;
	case d2l_ReqFinishAction:
		DoFinishAction(msg);
		break;
	case d2l_ReqSurrander:
		DoSurrander(msg);
		break;
	default:
		break;
	}*/
}

void FSGameManager::Tick()
{

}

void FSGameManager::DoGetReady(dMessage* msg)
{
	dGetReadyMsg* getReadyMsg = (dGetReadyMsg*)msg;

	m_Heros[PLAYSEQUENCE_FIRST].SetPlayerID(getReadyMsg->player[PLAYSEQUENCE_FIRST].nPlayerID);
	m_Heros[PLAYSEQUENCE_FIRST].SetProfession(getReadyMsg->player[PLAYSEQUENCE_FIRST].profession);
	m_Heros[PLAYSEQUENCE_FIRST].SetCards(getReadyMsg->player[PLAYSEQUENCE_FIRST].cards);

	m_Heros[PLAYSEQUENCE_SECOND].SetPlayerID(getReadyMsg->player[PLAYSEQUENCE_SECOND].nPlayerID);
	m_Heros[PLAYSEQUENCE_SECOND].SetProfession(getReadyMsg->player[PLAYSEQUENCE_SECOND].profession);
	m_Heros[PLAYSEQUENCE_SECOND].SetCards(getReadyMsg->player[PLAYSEQUENCE_SECOND].cards);

	CalcFirstAction();

	PLAYSEQUENCE otherPlayer = GetOtherPlayer();
	m_Heros[m_CurPlayer].DealCards(4);
	m_Heros[otherPlayer].DealCards(4);
	m_Heros[otherPlayer].DealSpecailCard(1);
	
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

void FSGameManager::DoChange(dMessage* msg)
{
	// ����
}

void FSGameManager::DoRoundAction(dMessage* msg)
{
	// �غ��еĲ���
}

void FSGameManager::DoFinishAction(dMessage* msg)
{
	// �غϽ����¼�
	SendRoundEndEvent();

	m_CurPlayer = GetOtherPlayer();
	m_Heros[m_CurPlayer].DealOneCard();

	// �غϿ�ʼ�¼�
	SendRoundBeginEvent();
}

void FSGameManager::DoSurrander(dMessage* msg)
{
}

void FSGameManager::SendRoundBeginEvent()
{

}

void FSGameManager::SendRoundEndEvent()
{

}
