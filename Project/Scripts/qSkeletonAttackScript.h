#pragma once
#include <Engine/qScript.h>

class qGameObject;

class qSkeletonAttackScript : public qScript
{
public:
	CLONE(qSkeletonAttackScript);
	qSkeletonAttackScript();
	~qSkeletonAttackScript();

public:
	virtual void Begin() override;
	virtual void Tick() override;

	virtual void BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;
	virtual void Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;
	virtual void EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;

	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;


private:
	float			m_SkeletonAttackDamage;
};

