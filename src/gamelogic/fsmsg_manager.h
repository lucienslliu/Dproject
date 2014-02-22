#pragma once

#include "fsmessage.h"

class FSMsgManager
{
public:
	FSMsgManager(void);
	~FSMsgManager(void);

	static FSMsgManager& Instance()
	{
		static FSMsgManager FSMM;
		return FSMM;
	}

public:
	void Init();

	void SendMessage();

};
