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
	RegisterMessage(FSUnitDeadMsg::Id);
	RegisterMessage(FSFinishRoundMsg::Id);
	RegisterMessage(FSSurranderMsg::Id);

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
	if (m_stat == EGameState_WaitPlayer && msgID == FSGetReadyMsg::Id)
	{
		DoGetReady(msg);
	}
	else if (m_stat == EGameState_Playing)
	{
		if (msgID == FSUseCardMsg::Id)
		{
			DoUseCard(msg);
		}
		else if (msgID == FSAttackMsg::Id)
		{
			DoAttack(msg);
		}
		else if (msgID == FSUnitDeadMsg::Id)
		{
			DoUnitDead(msg);
		}
		else if (msgID == FSFinishRoundMsg::Id)
		{
			DoFinishRound(msg);
		}
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

	m_Heros[m_CurPlayer].UseCard(useCardMsg->cardID, m_CurPlayer);
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
	// ���� ��ʱ����
	msg;
}

void FSGameManager::DoAttack(const Ptr<Message>& msg)
{
	// �غ��еĲ���
	Ptr<FSAttackMsg> attackMsg = boost::static_pointer_cast<FSAttackMsg>(msg);
	Ptr<FSUnit> pAttacker = FSUnitManager::Instance().FindUnit(attackMsg->attackerID);
	Ptr<FSUnit> pVictim = FSUnitManager::Instance().FindUnit(attackMsg->victimID);


	if (!pAttacker || !pVictim || (pAttacker == pVictim))
	{
		return;
	}

	if (attackMsg->GetPlayerID() != m_Heros[m_CurPlayer].GetPlayerID())
	{
		return;
	}

	if (m_CurPlayer != pAttacker->GetPlayer())
	{
		return;
	}

	// ����
	pAttacker->Attack(pVictim);
}

void FSGameManager::DoUnitDead(const Ptr<Message>& msg)
{
	// ��λ����
	Ptr<FSUnitDeadMsg> UnitDeadMsg = boost::static_pointer_cast<FSUnitDeadMsg>(msg);

	Ptr<FSUnit> pVictim = FSUnitManager::Instance().FindUnit(UnitDeadMsg->victimID);
	if (!pVictim)
	{
		return;
	}
	m_Heros[pVictim->GetPlayer()].KillUnit(UnitDeadMsg->victimID);
	FSUnitManager::Instance().DestroyUnit(pVictim);
}

void FSGameManager::DoFinishRound(const Ptr<Message>& msg)
{
	Ptr<FSFinishRoundMsg> finishRoundMsg = boost::static_pointer_cast<FSFinishRoundMsg>(msg);
	if (finishRoundMsg->GetPlayerID() != m_Heros[m_CurPlayer].GetPlayerID())
	{
		return;
	}

	// �غϽ����¼�
	SendRoundEndEvent();

	m_CurPlayer = GetOtherPlayer();
	m_Heros[m_CurPlayer].DealOneCard();

	// �غϿ�ʼ�¼�
	SendRoundBeginEvent();
}

void FSGameManager::DoSurrander(const Ptr<Message>& msg)
{
	Ptr<FSSurranderMsg> surranderMsg = boost::static_pointer_cast<FSSurranderMsg>(msg);

	// һ��Ͷ��
	GameOver(surranderMsg->GetPlayerID());
}

void FSGameManager::SendRoundBeginEvent()
{

}

void FSGameManager::SendRoundEndEvent()
{

}

void FSGameManager::GameOver(ID loser)
{
	loser;
}