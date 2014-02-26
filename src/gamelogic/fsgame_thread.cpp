#include "stdlogic.h"
#include "fsgame_thread.h"
#include <boost/bind.hpp>

#include "common_log.h"

#include "fsgame_world.h"

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
	FSGameWorld::Instance().Initialize();

	m_pThread.reset(new boost::thread(boost::bind(&FSGameThread::Loop, this)));
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
			// 这是个中断点
			//boost::this_thread::interruption_point();

			FSGameWorld::Instance().Run();

			// 这里也是中断点
			boost::this_thread::sleep(boost::posix_time::seconds(1));
		}

		;
	}
	catch (boost::thread_interrupted& /*e*/)
	{
		// 网上都说在中断点处会抛异常，但我在vs2008环境下没有捕获到
		// 你最好还是加上try-catch吧
		Log::Instance().Print("FSGameThread thread_interrupted!");
	}

}