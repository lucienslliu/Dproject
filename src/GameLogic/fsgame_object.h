#pragma once

#include "stdlogic.h"

class FSGameObject
{
public:
	FSGameObject(void);
	virtual ~FSGameObject(void);

	IID GetUniqueID() { return m_id; }
	void SetUniqueID(IID id) { m_id = id; }

private:
	IID m_id;
};
