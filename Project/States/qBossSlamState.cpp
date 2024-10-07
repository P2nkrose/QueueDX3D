#include "pch.h"
#include "qBossSlamState.h"
#include "qBossSlamFistState.h"
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include <Scripts/qBossScript.h>
#include <Scripts/qSlamScript.h>


qBossSlamState::qBossSlamState()
	: qState((UINT)STATE_TYPE::BOSSSLAMSTATE)
	, SlamHitbox(nullptr)
	, HitboxFlag(false)
{
}

qBossSlamState::~qBossSlamState()
{
}

void qBossSlamState::Enter()
{
	OGPos = GetOwner()->Transform()->GetRelativePos();
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativePos(OGPos.x, OGPos.y + 127.f, OGPos.z);
	GetOwner()->Transform()->SetRelativeScale(500.f, 600.f, 10.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.5f, 0.45f, 0.f));
	GetOwner()->Collider2D()->SetOffset(Vec3(0.13f, -0.24f, 0.f));

	GetOwner()->FlipBookComponent()->Play(4, 10, true);


	// 히트박스 (Fist) 생성
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	Ptr<qMaterial> pAlphaBlendMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DAlphaBlendMtrl");

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Player = pCurLevel->FindObjectByName(L"Player");

	qBossScript* BossScript = GetOwner()->GetScript<qBossScript>();
	Vec3 BossPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();

	SlamHitbox = new qGameObject;
	SlamHitbox->SetName(L"SlamHitbox");
	SlamHitbox->AddComponent(new qSlamScript);
	SlamHitbox->AddComponent(new qTransform);
	SlamHitbox->Transform()->SetRelativeScale(600.f, 360.f, 1.f);

	if (BossScript->GetBossDir() == DIRECTION::LEFT)
	{
		SlamHitbox->Transform()->SetRelativePos(Vec3(BossPos.x - 474.f, BossPos.y - 122.f, 30.f));
		SlamHitbox->Transform()->SetRelativeRotation(0.f, 3.141592f, 0.f);
	}
	else if (BossScript->GetBossDir() == DIRECTION::RIGHT)
	{
		SlamHitbox->Transform()->SetRelativePos(Vec3(BossPos.x + 474.f, BossPos.y - 122.f, 30.f));
	}

	SlamHitbox->AddComponent(new qMeshRender);
	SlamHitbox->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	SlamHitbox->MeshRender()->SetMaterial(pAlphaBlendMtrl);

	SlamHitbox->AddComponent(new qCollider2D);
	SlamHitbox->Collider2D()->SetScale(Vec3(0.f, 0.f, 1.f));
	

	SlamHitbox->AddComponent(new qFlipBookComponent);
	Ptr<qFlipBook> pSlamFist = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\boss_slamfist.flip");
	SlamHitbox->FlipBookComponent()->AddFlipBook(0, pSlamFist);

	SlamHitbox->AddComponent(new qFSM);
	SlamHitbox->FSM()->AddState(L"SlamFist", new qBossSlamFistState);

	SlamHitbox->FSM()->ChangeState(L"SlamFist");

	HitboxFlag = false;

	soundflag1 = false;
	soundflag2 = false;
	soundflag3 = false;
	soundflag4 = false;
	soundflag5 = false;
}

void qBossSlamState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 0 && !soundflag1)
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\boss\\slam1.wav", L"sound\\boss\\slam1.wav");
		pSound->Play(1, 0.4, true);

		soundflag1 = true;
	}
	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 2 && !soundflag2)
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\boss\\slamup.wav", L"sound\\boss\\slamup.wav");
		pSound->Play(1, 0.5, true);

		soundflag2 = true;
	}
	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 7 && !soundflag3)
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\boss\\slamdown.wav", L"sound\\boss\\slamdown.wav");
		pSound->Play(1, 0.5, true);

		soundflag3 = true;
	}
	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 8 && !soundflag4)
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\boss\\fistup.wav", L"sound\\boss\\fistup.wav");
		pSound->Play(1, 0.5, true);

		soundflag4 = true;
	}
	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 15 && !soundflag5)
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\boss\\fistdown.wav", L"sound\\boss\\fistdown.wav");
		pSound->Play(1, 0.5, true);

		soundflag5 = true;
	}



	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	// Index 맞춰서 히트박스 생성
	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 7 && !HitboxFlag)
	{
		pCurLevel->AddObject(8, SlamHitbox);
		HitboxFlag = true;
	}


	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"BossIdle");

		if (SlamHitbox != nullptr)
		{
			SlamHitbox->Destroy();
			SlamHitbox = nullptr;
			HitboxFlag = false;
		}
	}
}

void qBossSlamState::Exit()
{
	soundflag1 = false;
	soundflag2 = false;
	soundflag3 = false;
	soundflag4 = false;
	soundflag5 = false;

	GetOwner()->Transform()->SetRelativePos(OGPos);
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);

	if(HitboxFlag)
		HitboxFlag = false;
}
