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
	hDLL = LoadLibraryA("gamelogic.dll");//加载动态链接库MyDll.dll文件；
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

