#pragma once
#include <Engine/qScript.h>

class qGameObject;

class qSkeletonScript : public qScript
{
public:
	CLONE(qSkeletonScript);
	qSkeletonScript();
	~qSkeletonScript();

public:
	virtual void Begin() override;
	virtual void Tick() override;

	virtual void BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;
	virtual void Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;
	virtual void EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;

	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;

	virtual void Hit(float _Damage) override;

public:
	void SetSkeletonDir(DIRECTION _Dir) { m_CurUnitInfo.Dir = _Dir; }
	bool IsDirChanged() { return m_DirChanged; }
	DIRECTION GetSkeletonDir() { return m_CurUnitInfo.Dir; }
	tUnitInfo GetPrevInfo() { return m_PrevUnitInfo; }
	tUnitInfo GetUnitInfo() { return m_CurUnitInfo; }


private:
	Vec3		m_SkeletonPos;
	Vec3		m_SkeletonRot;

	DIRECTION	m_SkeletonDir;

	bool		m_DirChanged;

	float		m_Dir;
	float		m_BangTime;

	bool		Deathflag;

	float		m_SkeletonCollisionDamage;
};

