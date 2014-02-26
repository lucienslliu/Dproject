#pragma once

#include "igame_core.h"
#include <boost/thread/thread.hpp>

class FSGameThread
{
public:
	FSGameThread(void);
	~FSGameThread(void);

public:
	void Start();

	void Stop();

private:
	void Loop();

private:
	boost::shared_ptr<boost::thread> m_pThread;

	bool m_bStop;
};
