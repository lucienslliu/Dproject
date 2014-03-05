#include "stdlogic.h"
#include "fsgame_thread.h"
#include <boost/bind.hpp>

#include "common_log.h"
#include "fsmsg_manager.h"

FSGameThread::FSGameThread(void)
: m_bStop(false)
{
}

FSGameThread::~FSGameThread(void)
{
}

void FSGameThread::Start()
{
	Log::Instance().Init("fsgamelogic.log");
	Log::Instance().Print("FSGameThread Start!");
	FSMsgManager::Instance().Init();

	m_pThread.reset(new boost::thread(boost::bind(&FSGameThread::Loop, this)));

	Ptr<FSGetReadyMsg> msg(new FSGetReadyMsg());
	msg->SetPlayerID(0);
	FSMsgManager::Instance().SendSyncMessage(msg);
	msg->SetPlayerID(1);
	FSMsgManager::Instance().SendSyncMessage(msg);

	Ptr<FSUseCardMsg> msg1(new FSUseCardMsg());
	msg1->SetPlayerID(0);
	msg1->cardID = 0; 
	FSMsgManager::Instance().SendSyncMessage(msg1);

	msg1->SetPlayerID(1);
	msg1->cardID = 0; 
	FSMsgManager::Instance().SendSyncMessage(msg1);

	Ptr<FSAttackMsg> msg2(new FSAttackMsg());
	FSMsgManager::Instance().SendSyncMessage(msg2);
}

void FSGameThread::Stop()
{
	Log::Instance().Print("FSGameThread Stop!");
	m_bStop = true;
	//m_pThread->interrupt();
}

void FSGameThread::Loop()
{
	try
	{
		while (!m_bStop)
		{
			// ���Ǹ��жϵ�
			boost::this_thread::interruption_point();

			// ����Ҳ���жϵ�
			boost::this_thread::sleep(boost::posix_time::seconds(1));
		}

		Log::Instance().Print("Logic thread End!");
	}
	catch (boost::thread_interrupted& /*e*/)
	{
		// ���϶�˵���жϵ㴦�����쳣��������vs2008������û�в���
		// ����û��Ǽ���try-catch��
		Log::Instance().Print("FSGameThread thread_interrupted!");
	}

}