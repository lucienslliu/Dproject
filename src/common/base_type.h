#pragma once

#include "boost/smart_ptr/shared_ptr.hpp"

#ifdef Ptr
#undef Ptr
#endif
#define Ptr boost::shared_ptr

#ifdef interface
#undef interface
#endif
#define interface struct

#define ASSERT assert

#define INVALID_ID -1
#define INVALID_INDEX -1

typedef int ID;

enum EMessageType
{
	EM_MessageBegin,
	EM_Message = EM_MessageBegin,
	EM_FSMessage = EM_MessageBegin,
	EM_FSSyncMessage = EM_MessageBegin,
	EM_FSAsyncMessage = EM_MessageBegin,
	EM_FSGetReadyMsg = EM_MessageBegin,
	EM_FSUseCardMsg,
	EM_FSUnitDeadMsg,
	EM_FSAttackMsg,
	EM_FSFinishRoundMsg,
	EM_FSSurranderMsg,
};

