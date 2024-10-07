#pragma once
#include <Engine/qScript.h>

class qGameObject;

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
	virtual void Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;
	virtual void EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;

	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;

public:
	DIRECTION GetPlayerDir() { return m_CurUnitInfo.Dir; }
	tUnitInfo GetPrevInfo() { return m_PrevUnitInfo; }
	tUnitInfo GetUnitInfo() { return m_CurUnitInfo; }
	
	void SetPlayerDir(DIRECTION _Dir) { m_CurUnitInfo.Dir = _Dir; }
	bool IsDirChanged() { return m_DirChanged; }

	bool IsDash() { return m_IsDash; }
	bool IsDashCoolTime() { return m_IsDashCoolTime; }
	void SetDash(bool _IsDash) { m_IsDash = _IsDash; m_IsDashCoolTime = _IsDash; }
	void SetLock(bool _Lock) { m_DirLock = _Lock; }

	void ResetCombo() { m_NextCombo = 1; }
	void PlayCombo();

	void Jump();
	void RestoreJumpCount()	{ m_CurJumpCount = 0; }
	
	virtual void Hit(float _Damage) override;


public:
	// ÇÃ·§Æû À§Ä¡¸¦ ¼³Á¤
	void SetCurrentPlatformPos(const Vec3& _PlatformPos) { m_CurrentPlatformPos = _PlatformPos; }
	Vec3 GetCurrentPlatformPos() const { return m_CurrentPlatformPos; }

public:
	int GetFiveDamageCount() { return m_FiveDamageCount; }
	int GetTenDamageCount() { return m_TenDamageCount; }
	
	void SetCountZero() { m_FiveDamageCount = 0; m_TenDamageCount = 0; }

	void PlusFiveDamageCount() { m_FiveDamageCount += 1; }
	void PlusTenDamageCount() { m_TenDamageCount += 1; }


private:
	Vec3				m_CurrentPlatformPos;	// ÇöÀç Ãæµ¹ÇÑ ÇÃ·§ÆûÀÇ À§Ä¡

	qGameObject*		RightBook;
	qGameObject*		LeftBook;


	Vec3				m_PlayerPos;
	Vec3				m_PlayerRot;

	float				m_Speed;
	Ptr<qTexture>		m_Texture;
	Ptr<qPrefab>		m_MissilePref;
	Ptr<qPrefab>		m_BookPref;

	DIRECTION			m_PlayerDir;
	float				m_Dir;

	bool				m_DirLock;
	bool				m_DirChanged;
	bool				m_IsDash;
	bool				m_IsDashCoolTime;

	float				m_DashCoolTime;

	int					m_NextCombo;

	int					m_CurJumpCount;
	int					m_DoubleJumpCount;

	int					m_FiveDamageCount;
	int					m_TenDamageCount;
};


