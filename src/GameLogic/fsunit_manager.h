#pragma once

#include "fsunit.h"
#include "stdlogic.h"

class FSUnitManager
{
public:
	FSUnitManager(void);
	~FSUnitManager(void);

public:
	FSUnit* CreateUnit();

	void DestroyUnit(FSUnit* unit);

	void DestroyUnit(ID unitID);

	void Update();

private:
	typedef std::map<ID, FSUnit*> UNITMAP;
	UNITMAP m_unitmap;
};
