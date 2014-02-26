#pragma once

class IGameCore
{
public:
	virtual bool Initialize() = 0;

	virtual bool UnInit() = 0;

	virtual void SendMessage() = 0;

};
#ifdef __cplusplus
extern "C" {  // only need to export C interface if
	// used by C++ source code
#endif

	__declspec(dllexport) IGameCore* CreateGameCore();

#ifdef __cplusplus
}
#endif