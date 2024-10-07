#pragma once
#include <Engine/qScript.h>

class qGameObject;

class qGhostScript : public qScript
{
public:
	CLONE(qGhostScript);
	qGhostScript();
	~qGhostScript();

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
	void SetGhostDir(DIRECTION _Dir) { m_CurUnitInfo.Dir = _Dir; }
	bool IsDirChanged() { return m_DirChanged; }
	DIRECTION GetGhostDir() { return m_CurUnitInfo.Dir; }
	tUnitInfo GetPrevInfo() { return m_PrevUnitInfo; }
	tUnitInfo GetUnitInfo() { return m_CurUnitInfo; }


private:
	DIRECTION	m_GhostDir;
	bool		m_DirChanged;

	float		m_BangTime;
	bool		Deathflag;


	float		m_GhostCollisionDamage;
};

