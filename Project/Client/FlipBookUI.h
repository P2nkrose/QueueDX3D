#pragma once
#include "AssetUI.h"

class FlipBookUI : public AssetUI
{
public:
	FlipBookUI();
	~FlipBookUI();

public:
	virtual void Update() override;


private:
	int			m_FlipBookIdx;
};

