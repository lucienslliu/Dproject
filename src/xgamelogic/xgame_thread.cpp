#include "stdlogic.h"
#include "xgame_thread.h"
#include <boost/bind.hpp>

#include "common_log.h"
#include "xmsg_manager.h"

XGameThread::XGameThread(void)
: m_bStop(false)
{
}

XGameThread::~XGameThread(void)
{
}

void XGameThread::Start()
{
	Log::Instance().Init("fsgamelogic.log");
	Log::Instance().Print("XGameThread Start!");

	XMsgManager::Instance().Init();

	m_pThread.reset(new boost::thread(boost::bind(&XGameThread::Loop, this)));
}

void XGameThread::Stop()
{
	Log::Instance().Print("XGameThread Stop!");
	m_bStop = true;
	//m_pThread->interrupt();
}

void XGameThread::Loop()
{
	try
	{
		while (!m_bStop)
		{
			// ���Ǹ��жϵ�
			boost::this_thread::interruption_point();

			// ����Ҳ���жϵ�
			boost::this_thread::sleep(boost::posix_time::seconds(1));

			XMsgManager::Instance().Tick();
		}

		Log::Instance().Print("Logic thread End!");
	}
	catch (boost::thread_interrupted& /*e*/)
	{
		// ���϶�˵���жϵ㴦�����쳣��������vs2008������û�в���
		// ����û��Ǽ���try-catch��
		Log::Instance().Print("XGameThread thread_interrupted!");
	}

}