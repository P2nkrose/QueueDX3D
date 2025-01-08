#pragma once
#include "ComponentUI.h"

class LandScapeUI : public ComponentUI
{
public:
	LandScapeUI();
	virtual ~LandScapeUI();

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	void ChangeBrushIndex(DWORD_PTR _Param);

private:

};

