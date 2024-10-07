#pragma once
#include <Engine/qScript.h>

class qBossHUDScript : public qScript
{
public:
	CLONE(qBossHUDScript);
	qBossHUDScript();
	~qBossHUDScript();


public:
	virtual void Begin() override;
	virtual void Tick() override;
	virtual void BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;


public:
	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;


public:
	float GetCurBossHP() { return m_CurBossHP; }
	void SetCurBossHP(float _ratio) { m_CurBossHP = _ratio; }


private:
	float			m_MaxBossHP;
	float			m_CurBossHP;
	float			m_DamageHP;

	int				m_10Count;
	int				m_20Count;
	int				m_30Count;
	int				m_40Count;
	int				m_50Count;
};

