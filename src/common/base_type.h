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
