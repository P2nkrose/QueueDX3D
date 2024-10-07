#pragma once
#include <Engine/qScript.h>

class qGameObject;

class qPlayerHitboxScript : public qScript
{
public:
	CLONE(qPlayerHitboxScript);
	qPlayerHitboxScript();
	qPlayerHitboxScript(const qPlayerHitboxScript& _Origin);
	~qPlayerHitboxScript();

	virtual void Begin() override;
	virtual void Tick() override;

public:
	void On();
	void Off();

	void Activate();


public:
	virtual void BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;
	virtual void Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;
	virtual void EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;

	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;


private:
	float	m_Damage;

	float	m_Acc;
	float	m_StartTime;
	float	m_Duration;

	bool	m_Active;
	bool	m_IsColliderActive;

	Vec3    m_ColOffset;
	Vec3    m_ColScale;
};

