#pragma once
#include <Engine/qScript.h>

class qCollectScript : public qScript
{
public:
	CLONE(qCollectScript);
	qCollectScript();
	~qCollectScript();


public:
	virtual void Begin() override;
	virtual void Tick() override;
	virtual void BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;


public:
	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;


private:
	Vec3			m_PlayPos;
	Vec3			m_OptionPos;
	Vec3			m_CreditPos;
	Vec3			m_ExitPos;
};

