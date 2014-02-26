// DGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../src/gamelogic/igame_core.h"
#include <Windows.h>
#include <iostream>

extern "C" _declspec(dllimport) int Test();

int _tmain(int argc, _TCHAR* argv[])
{
	int i = Test();
	
	typedef IGameCore* (CALLBACK *CreateGameCore)();

	HINSTANCE hDLL;
	CreateGameCore createGameCore;
	DWORD dwErr = 0;
	hDLL = LoadLibraryA("gamelogic.dll");//���ض�̬���ӿ�MyDll.dll�ļ���
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

