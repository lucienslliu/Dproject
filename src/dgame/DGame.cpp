// DGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../GameLogic/fsgame_object.h"

extern "C" _declspec(dllimport) int Test();

int _tmain(int argc, _TCHAR* argv[])
{
	int i = Test();
	

	return 0;
}

