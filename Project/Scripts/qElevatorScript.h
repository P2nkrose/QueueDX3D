#pragma once
#include <Engine/qScript.h>

class qElevatorScript : public qScript
{
public:
	CLONE(qElevatorScript);
	qElevatorScript();
	~qElevatorScript();


public:
	virtual void Begin() override;
	virtual void Tick() override;

	virtual void BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;
	virtual void Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;
	virtual void EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;

public:
	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;


private:
	Vec3		FixPos;
};

