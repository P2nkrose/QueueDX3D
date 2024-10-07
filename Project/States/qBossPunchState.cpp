#include "pch.h"
#include "qBossPunchState.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include <Scripts/qBossScript.h>
#include <Scripts/qPunchScript.h>

qBossPunchState::qBossPunchState()
	: qState((UINT)STATE_TYPE::BOSSPUNCHSTATE)
	, PunchHitbox(nullptr)
	, HitboxFlag(false)
{
}

qBossPunchState::~qBossPunchState()
{
}

void qBossPunchState::Enter()
{
	OGPos = GetOwner()->Transform()->GetRelativePos();
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	qBossScript* BossScript = GetOwner()->GetScript<qBossScript>();
	if (BossScript->GetBossDir() == DIRECTION::LEFT)
	{
		GetOwner()->Transform()->SetRelativePos(OGPos.x - 70.f, OGPos.y + 16.f, OGPos.z);
	}
	else if (BossScript->GetBossDir() == DIRECTION::RIGHT)
	{
		GetOwner()->Transform()->SetRelativePos(OGPos.x + 70.f, OGPos.y + 16.f, OGPos.z);
	}

	GetOwner()->Transform()->SetRelativeScale(1500.f, 370.f, 10.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.16f, 0.72f, 1.f));
	GetOwner()->Collider2D()->SetOffset(Vec3(0.f, -0.09f, 0.f));

	GetOwner()->FlipBookComponent()->Play(3, 25, true);



	// 히트박스 생성
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");

	Vec3 BossPos = GetOwner()->Transform()->GetRelativePos();

	PunchHitbox = new qGameObject;
	PunchHitbox->SetName(L"PunchHitbox");
	PunchHitbox->AddComponent(new qPunchScript);
	PunchHitbox->AddComponent(new qTransform);

	if (BossScript->GetBossDir() == DIRECTION::LEFT)
	{
		PunchHitbox->Transform()->SetRelativePos(Vec3(BossPos.x - 387.f, BossPos.y - 45.f, BossPos.z));
	}
	else if (BossScript->GetBossDir() == DIRECTION::RIGHT)
	{
		PunchHitbox->Transform()->SetRelativePos(Vec3(BossPos.x + 387.f, BossPos.y - 45.f, BossPos.z));
	}

	PunchHitbox->Transform()->SetRelativeScale(535.f, 154.f, 1.f);

	PunchHitbox->AddComponent(new qCollider2D);
	PunchHitbox->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	HitboxFlag = false;


	soundflag1 = false;
	soundflag2 = false;
}

void qBossPunchState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 5 && !soundflag1)
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\boss\\punch1.wav", L"sound\\boss\\punch1.wav");
		pSound->Play(1, 0.5, true);

		soundflag1 = true;
	}

	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 25 && !soundflag2)
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\boss\\punch2.wav", L"sound\\boss\\punch2.wav");
		pSound->Play(1, 0.5, true);

		soundflag2 = true;
	}


	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	// Index 맞춰서 히트박스 생성하기
	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 31 && !HitboxFlag)
	{
		pCurLevel->AddObject(8, PunchHitbox);
		HitboxFlag = true;
	}



	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"BossIdle");

		if (PunchHitbox != nullptr)
		{
			PunchHitbox->Destroy();
			PunchHitbox = nullptr;
			HitboxFlag = false;
		}
	}
}

void qBossPunchState::Exit()
{
	soundflag1 = false;
	soundflag2 = false;


	GetOwner()->Transform()->SetRelativePos(OGPos);
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);

	if (HitboxFlag)
		HitboxFlag = false;

	if (PunchHitbox != nullptr)
	{
		PunchHitbox->Destroy();
	}
}
