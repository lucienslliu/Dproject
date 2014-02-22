#pragma once

#include "boost/smart_ptr/shared_ptr.hpp"

#define INVALID_ID -1
#define INVALID_INDEX -1
#define CARDS_TOTALNUM 30

#define Ptr boost::shared_ptr
#define interface struct

#define ASSERT assert

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

typedef int ID;
typedef int IID;
typedef int CARD_ID;
