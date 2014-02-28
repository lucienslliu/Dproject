#pragma once

#include "stdlogic.h"

extern "C" _declspec(dllexport) int Test();

class FSGameObject
{
public:
	FSGameObject(void);
	virtual ~FSGameObject(void);

	ID GetUniqueID() { return m_id; }
	void SetUniqueID(ID id) { m_id = id; }

private:
	ID m_id;
};
