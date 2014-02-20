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

	void DestroyUnit(IID unitID);

	void Update();

private:
	typedef std::map<IID, FSUnit*> UNITMAP;
	UNITMAP m_unitmap;
};
