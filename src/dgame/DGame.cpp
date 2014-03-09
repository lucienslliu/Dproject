// DGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>

#include "../common/common_log.h"
#include "../src/gamelogic/igame_core.h"
#include "fsmessage.h"

extern "C" _declspec(dllimport) int Test();


void SendFSMessage(IGameCore* pCore)
{
	if (!pCore)
	{
		return;
	}
	// 准备
	Ptr<FSGetReadyMsg> msg(new FSGetReadyMsg());
	msg->SetPlayerID(0);
	pCore->SendMessage(msg);
	msg->SetPlayerID(1);
	pCore->SendMessage(msg);

	// 第一个人使用牌
	Ptr<FSUseCardMsg> msg1(new FSUseCardMsg());
	msg1->SetPlayerID(0);
	msg1->cardID = 0; 
	pCore->SendMessage(msg1);

	// 第一个人结束回合
	Ptr<FSFinishRoundMsg> finishRound(new FSFinishRoundMsg());
	finishRound->SetPlayerID(0);
	pCore->SendMessage(finishRound);

	// 第二个人使用牌
	msg1->SetPlayerID(1);
	msg1->cardID = 0; 
	pCore->SendMessage(msg1);

	// 第二个人结束回合
	finishRound.reset(new FSFinishRoundMsg());
	finishRound->SetPlayerID(1);
	pCore->SendMessage(finishRound);

	// 第一个玩家发起攻击
	Ptr<FSAttackMsg> attackMsg(new FSAttackMsg());
	attackMsg->SetPlayerID(0);
	attackMsg->attackerID = 1;
	attackMsg->victimID = 2;
	pCore->SendMessage(attackMsg);

	// 第一个玩家投降
	Ptr<FSSurranderMsg> surranderMsg(new FSSurranderMsg());
	surranderMsg->SetPlayerID(0);
	pCore->SendMessage(surranderMsg);
}


int _tmain(int argc, _TCHAR* argv[])
{
	int i = Test();
	
	typedef IGameCore* (CALLBACK *CreateGameCore)();

	HINSTANCE hDLL;
	CreateGameCore createGameCore;
	DWORD dwErr = 0;
	hDLL = LoadLibraryA("gamelogic.dll");//加载动态链接库MyDll.dll文件；
	if (hDLL)
	{
		createGameCore = (CreateGameCore)GetProcAddress(hDLL, "CreateGameCore");
		if (createGameCore)
		{
			IGameCore* pCore = createGameCore();
			if (pCore)
			{
				pCore->Initialize();

				SendFSMessage(pCore);

				char ch;
				if (std::cin >> ch && ch == 'y')
				{
					pCore->UnInit();
// 					Log::Instance().Init("test.log");
// 					Log::Instance().Print("test!");
				}
			}
		}
		else
		{
			dwErr = GetLastError();
		}
	}

	return 0;
}

