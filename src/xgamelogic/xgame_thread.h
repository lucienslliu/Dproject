#pragma once

#include "igame_core.h"
#include <boost/thread/thread.hpp>

class XGameThread
{
public:
	XGameThread(void);
	~XGameThread(void);

public:
	void Start();

	void Stop();

private:
	void Loop();

private:
	Ptr<boost::thread> m_pThread;

	bool m_bStop;
};
