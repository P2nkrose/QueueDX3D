#include "pch.h"
#include "qSkeletonAttackState.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include <Scripts/qSkeletonScript.h>
#include <Scripts/qSkeletonAttackScript.h>

qSkeletonAttackState::qSkeletonAttackState()
	: qState((UINT)STATE_TYPE::SKELETONATTACKSTATE)
	, SkeletonAttackHitBox(nullptr)
{
}

qSkeletonAttackState::~qSkeletonAttackState()
{
}

void qSkeletonAttackState::Enter()
{
	OGPos = GetOwner()->Transform()->GetRelativePos();
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();
	//OGColOffset = GetOwner()->Collider2D()->GetOffset();

	GetOwner()->Transform()->SetRelativePos(OGPos.x + 15.f, OGPos.y - 5.f, 10.f);
	GetOwner()->Transform()->SetRelativeScale(340.f, 160.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.5f, 1.0f, 0.f));
	//GetOwner()->Collider2D()->SetOffset(Vec3(-15.f, 5.f, 0.f));

	GetOwner()->FlipBookComponent()->Play(1, 15, false);



	// 히트박스 생성
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	qSkeletonScript* SkeletonScript = GetOwner()->GetScript<qSkeletonScript>();
	Vec3 SkeleonPos = GetOwner()->Transform()->GetRelativePos();

	SkeletonAttackHitBox = new qGameObject;
	SkeletonAttackHitBox->SetName(L"SkeletonAttackHitbox");
	SkeletonAttackHitBox->AddComponent(new qSkeletonAttackScript);
	SkeletonAttackHitBox->AddComponent(new qTransform);
	SkeletonAttackHitBox->Transform()->SetRelativeScale(90.f, 140.f, 1.f);

	if (SkeletonScript->GetSkeletonDir() == DIRECTION::LEFT)
	{
		SkeletonAttackHitBox->Transform()->SetRelativePos(Vec3(SkeleonPos.x - 120.f, SkeleonPos.y, SkeleonPos.z));
	}
	else if (SkeletonScript->GetSkeletonDir() == DIRECTION::RIGHT)
	{
		SkeletonAttackHitBox->Transform()->SetRelativePos(Vec3(SkeleonPos.x + 120.f, SkeleonPos.y, SkeleonPos.z));
	}

	SkeletonAttackHitBox->AddComponent(new qCollider2D);
	SkeletonAttackHitBox->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));


	soundflag = false;
}

void qSkeletonAttackState::FinalTick()
{
	if (!soundflag)
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\monster\\skeleton\\attack.wav", L"sound\\monster\\skeleton\\attack.wav");
		pSound->Play(1, 0.5, true);

		soundflag = true;
	}


	static bool hitbox = false;

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 12 && !hitbox)
	{
		pCurLevel->AddObject(6, SkeletonAttackHitBox);
		hitbox = true;
	}

	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"SkeletonIdle");

		if (SkeletonAttackHitBox != nullptr)
		{
			SkeletonAttackHitBox->Destroy();
			SkeletonAttackHitBox = nullptr;
			hitbox = false;
		}
	}
}

void qSkeletonAttackState::Exit()
{
	soundflag = false;

	GetOwner()->Transform()->SetRelativePos(OGPos);
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
	//GetOwner()->Collider2D()->SetOffset(OGColOffset);
}
