#include "stdlogic.h"
#include "fsgame_thread.h"
#include <boost/bind.hpp>

FSGameThread::FSGameThread(void)
: m_bStop(false)
{
}

FSGameThread::~FSGameThread(void)
{
}

void FSGameThread::Start()
{
	m_pThread.reset(new boost::thread(boost::bind(&FSGameThread::Loop, this)));
}

void FSGameThread::Stop()
{
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

		int i = 1;
	}
	catch (boost::thread_interrupted& /*e*/)
	{
		// ���϶�˵���жϵ㴦�����쳣��������vs2008������û�в���
		// ����û��Ǽ���try-catch��
		int i = 0;
	}

}