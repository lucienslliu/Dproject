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
typedef int CARD_ID;

#define CARDS_TOTALNUM 30

enum PLAYSEQUENCE
{
	PLAYSEQUENCE_FIRST,
	PLAYSEQUENCE_SECOND,
	PLAYSEQUENCE_COUNT
};

enum UNIT_TYPE
{
	UNIT_TYPE_1,
	UNIT_TYPE_2,
	UNIT_TYPE_3,
	UNIT_TYPE_COUNT,
};

enum HERO_PROFESSION
{
	HERO_PROFESSION_1,
	HERO_PROFESSION_2,
	HERO_PROFESSION_3,
	PROFESSION_COUNT
};


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

