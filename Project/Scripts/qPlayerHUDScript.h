#pragma once
#include <Engine/qScript.h>

class qPlayerHUDScript : public qScript
{
public:
	CLONE(qPlayerHUDScript);
	qPlayerHUDScript();
	~qPlayerHUDScript();


public:
	virtual void Begin() override;
	virtual void Tick() override;
	virtual void BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;


public:
	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;


public:
	float GetCurPlayerHP() { return m_CurPlayerHP; }
	void SetCurPlayerHP(float _ratio) { m_CurPlayerHP = _ratio; }


private:
	float			m_MaxPlayerHP;
	float			m_CurPlayerHP;
	float			m_DamageHP;

	int				m_FiveCount;
	int				m_TenCount;
};

