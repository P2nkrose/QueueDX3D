#include "pch.h"
#include "qDrownedAttackState.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include <Scripts/qDrownedScript.h>
#include <Scripts/qDrownedAttackScript.h>


qDrownedAttackState::qDrownedAttackState()
	: qState((UINT)STATE_TYPE::DROWNEDATTACKSTATE)
	, DrownedAttackHitbox(nullptr)
{
}

qDrownedAttackState::~qDrownedAttackState()
{
}

void qDrownedAttackState::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(350.f, 230.f, 10.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.42f, 1.f, 1.f));

	GetOwner()->FlipBookComponent()->Play(3, 10, false);

	
	// 히트박스 생성
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	qDrownedScript* DrownedScript = GetOwner()->GetScript<qDrownedScript>();
	Vec3 DrownedPos = GetOwner()->Transform()->GetRelativePos();

	DrownedAttackHitbox = new qGameObject;
	DrownedAttackHitbox->SetName(L"DrownedAttackHitbox");
	DrownedAttackHitbox->AddComponent(new qDrownedAttackScript);
	DrownedAttackHitbox->AddComponent(new qTransform);
	DrownedAttackHitbox->Transform()->SetRelativeScale(90.f, 130.f, 1.f);

	if (DrownedScript->GetDrownedDir() == DIRECTION::LEFT)
	{
		DrownedAttackHitbox->Transform()->SetRelativePos(Vec3(DrownedPos.x - 120.f, DrownedPos.y, DrownedPos.z));
	}
	else if (DrownedScript->GetDrownedDir() == DIRECTION::RIGHT)
	{
		DrownedAttackHitbox->Transform()->SetRelativePos(Vec3(DrownedPos.x + 120.f, DrownedPos.y, DrownedPos.z));
	}

	DrownedAttackHitbox->AddComponent(new qCollider2D);
	DrownedAttackHitbox->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	
}

void qDrownedAttackState::FinalTick()
{
	static bool hitbox = false;

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	// Index 맞춰서 히트박스 생성하기
	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 15 && !hitbox)
	{
		pCurLevel->AddObject(6, DrownedAttackHitbox);
		hitbox = true;

		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\monster\\drowned\\attack.wav", L"sound\\monster\\drowned\\attack.wav");
		pSound->Play(1, 0.5, true);
	}

	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"DrownedIdle");

		if (DrownedAttackHitbox != nullptr)
		{
			DrownedAttackHitbox->Destroy();
			DrownedAttackHitbox = nullptr;
			hitbox = false;
		}
	}
}

void qDrownedAttackState::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
