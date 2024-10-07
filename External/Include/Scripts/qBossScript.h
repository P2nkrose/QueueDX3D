#pragma once
#include <Engine/qScript.h>

class qGameObject;

class qBossScript : public qScript
{
public:
	CLONE(qBossScript);
	qBossScript();
	~qBossScript();

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
	void SetBossDir(DIRECTION _Dir) { m_CurUnitInfo.Dir = _Dir; }
	DIRECTION GetBossDir() { return m_CurUnitInfo.Dir; }
	bool IsDirChanged() { return m_DirChanged; }

	tUnitInfo GetPrevInfo() { return m_PrevUnitInfo; }
	tUnitInfo GetUnitInfo() { return m_CurUnitInfo; }

public:
	int Get10Damagecount() { return m_10DamageCount; }
	int Get20Damagecount() { return m_20DamageCount; }
	int Get30Damagecount() { return m_30DamageCount; }
	int Get40Damagecount() { return m_40DamageCount; }
	int Get50Damagecount() { return m_50DamageCount; }

	void Plus10DamageCount() { m_10DamageCount += 1; }
	void Plus20DamageCount() { m_20DamageCount += 1; }
	void Plus30DamageCount() { m_30DamageCount += 1; }
	void Plus40DamageCount() { m_40DamageCount += 1; }
	void Plus50DamageCount() { m_50DamageCount += 1; }




private:
	Vec3				m_BossPos;
	Vec3				m_BossRot;

	float				m_Speed;
	DIRECTION			m_BossDir;
	
	bool				m_DirChanged;

	float				m_BangTime;

	float				m_BossColiisionDamage;

	int					m_10DamageCount;
	int					m_20DamageCount;
	int					m_30DamageCount;
	int					m_40DamageCount;
	int					m_50DamageCount;
};

