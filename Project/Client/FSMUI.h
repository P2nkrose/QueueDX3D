#pragma once
#include "ComponentUI.h"

class FSMUI : public ComponentUI
{
public:
	FSMUI();
	~FSMUI();

public:
	virtual void Update() override;
};

