#pragma once
#include "qScript.h"

class qPlayerScript : public qScript
{
public:
	CLONE(qPlayerScript);
	qPlayerScript();
	~qPlayerScript();

public:
	virtual void Begin() override;
	virtual void Tick() override;

	virtual void BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;

private:
	float		m_Speed;
};

