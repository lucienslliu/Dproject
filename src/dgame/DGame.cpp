// DGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../src/gamelogic/igame_core.h"
#include <Windows.h>

extern "C" _declspec(dllimport) int Test();

int _tmain(int argc, _TCHAR* argv[])
{
	int i = Test();
	
	typedef int (CALLBACK *CreateGameCore)();

	HINSTANCE hDLL;
	CreateGameCore createGameCore;
	DWORD dwErr = 0;
	hDLL = LoadLibraryA("gamelogic.dll");//���ض�̬���ӿ�MyDll.dll�ļ���
	if (hDLL)
	{
		createGameCore = (CreateGameCore)GetProcAddress(hDLL, "CreateGameCore");
		if (createGameCore)
		{
			int pCore = createGameCore();
			pCore = 0;
		}
		else
		{
			dwErr = GetLastError();
		}
	}

	return 0;
}

