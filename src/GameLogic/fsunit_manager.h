#pragma once

#include "fsunit.h"
#include "stdlogic.h"

class FSUnitManager
{
public:
	FSUnitManager(void);
	~FSUnitManager(void);

	bool Init();

	static FSUnitManager& Instance()
	{
		static FSUnitManager UM;
		return UM;
	}

public:
	Ptr<FSUnit> CreateUnit();

	void DestroyUnit(Ptr<FSUnit> unit);

	void DestroyUnit(ID unitID);

	void Update();

	Ptr<FSUnit> FindUnit(ID unitID);

	void UpdateDeadUnit(Ptr<FSUnit> unit);

private:
	typedef std::map<ID, Ptr<FSUnit> > UNITMAP;
	UNITMAP m_unitmap;
};
