#pragma once
#include <Engine/qScript.h>

class qRangeScript : public qScript
{
public:
	CLONE(qRangeScript);
	qRangeScript();
	~qRangeScript();


public:
	virtual void Begin() override;
	virtual void Tick() override;
	virtual void BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;


public:
	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;


private:
	float		m_RangeDamage;
};

