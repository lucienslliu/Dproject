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
			// 这是个中断点
			boost::this_thread::interruption_point();

			// 这里也是中断点
			boost::this_thread::sleep(boost::posix_time::seconds(1));
		}

		int i = 1;
	}
	catch (boost::thread_interrupted& /*e*/)
	{
		// 网上都说在中断点处会抛异常，但我在vs2008环境下没有捕获到
		// 你最好还是加上try-catch吧
		int i = 0;
	}

}