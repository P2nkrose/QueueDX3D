#pragma once
#include <Engine/qGameObject.h>


class qGameObjectEx : public qGameObject
{
public:
	CLONE(qGameObjectEx);


public:
	virtual void FinalTick() override;
};

