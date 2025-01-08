#pragma once
#include "ComponentUI.h"

class SkyBoxUI : public ComponentUI
{
public:
	SkyBoxUI();
	virtual ~SkyBoxUI();

public:
	virtual void Update() override;

private:
	void ChangeSkybox(DWORD_PTR Param);

};

