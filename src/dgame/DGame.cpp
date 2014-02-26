// DGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../src/gamelogic/igame_core.h"
#include <Windows.h>
#include <iostream>

#include "../common/common_log.h"

extern "C" _declspec(dllimport) int Test();

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

