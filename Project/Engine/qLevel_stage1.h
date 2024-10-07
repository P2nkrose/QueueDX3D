#pragma once
#include "qLevel.h"

class qLevel_stage1 : public qLevel
{
public:
	qLevel_stage1();
	~qLevel_stage1();

	virtual void Begin() override;
	virtual void Tick() override;
	virtual void FinalTick() override;




};

