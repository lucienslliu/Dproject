// DGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>

#include "../common/common_log.h"
#include "../src/xgamelogic/igame_core.h"
#include "fsmessage.h"

extern "C" _declspec(dllimport) int Test();


void SendXMessage(IGameCore* pCore)
{
	if (!pCore)
	{
		return;
	}
	// ׼��
// 	Ptr<FSGetReadyMsg> msg(new FSGetReadyMsg());
// 	msg->SetPlayerID(0);
// 	pCore->SendMessage(msg);
// 	msg->SetPlayerID(1);
// 	pCore->SendMessage(msg);
// 
// 	// ��һ����ʹ����
// 	Ptr<FSUseCardMsg> msg1(new FSUseCardMsg());
// 	msg1->SetPlayerID(0);
// 	msg1->cardID = 0; 
// 	pCore->SendMessage(msg1);
// 
// 	// ��һ���˽����غ�
// 	Ptr<FSFinishRoundMsg> finishRound(new FSFinishRoundMsg());
// 	finishRound->SetPlayerID(0);
// 	pCore->SendMessage(finishRound);
// 
// 	// �ڶ�����ʹ����
// 	msg1->SetPlayerID(1);
// 	msg1->cardID = 0; 
// 	pCore->SendMessage(msg1);
// 
// 	// �ڶ����˽����غ�
// 	finishRound.reset(new FSFinishRoundMsg());
// 	finishRound->SetPlayerID(1);
// 	pCore->SendMessage(finishRound);
// 
// 	// ��һ����ҷ��𹥻�
// 	Ptr<FSAttackMsg> attackMsg(new FSAttackMsg());
// 	attackMsg->SetPlayerID(0);
// 	attackMsg->attackerID = 1;
// 	attackMsg->victimID = 2;
// 	pCore->SendMessage(attackMsg);
// 
// 	// ��һ�����Ͷ��
// 	Ptr<FSSurranderMsg> surranderMsg(new FSSurranderMsg());
// 	surranderMsg->SetPlayerID(0);
// 	pCore->SendMessage(surranderMsg);
}


int _tmain(int argc, _TCHAR* argv[])
{
	int i = Test();
	
	typedef IGameCore* (CALLBACK *CreateGameCore)();

	HINSTANCE hDLL;
	CreateGameCore createGameCore;
	DWORD dwErr = 0;
	hDLL = LoadLibraryA("xgamelogic.dll");//���ض�̬���ӿ�MyDll.dll�ļ���
	if (hDLL)
	{
		createGameCore = (CreateGameCore)GetProcAddress(hDLL, "CreateGameCore");
		if (createGameCore)
		{
			IGameCore* pCore = createGameCore();
			if (pCore)
			{
				pCore->Initialize();

				SendXMessage(pCore);

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

