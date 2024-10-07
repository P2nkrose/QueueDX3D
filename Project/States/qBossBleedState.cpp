#include "pch.h"
#include "qBossBleedState.h"
#include "qBossBleedWaveState.h"
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include <Scripts/qBossScript.h>
#include <Scripts/qBleedScript.h>

qBossBleedState::qBossBleedState()
	: qState((UINT)STATE_TYPE::BOSSBLEEDSTATE)
	, BleedHitbox(nullptr)
	, HitboxFlag(false)
{
}

qBossBleedState::~qBossBleedState()
{
}

void qBossBleedState::Enter()
{
	OGPos = GetOwner()->Transform()->GetRelativePos();
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	qBossScript* BossScript = GetOwner()->GetScript<qBossScript>();
	if (BossScript->GetBossDir() == DIRECTION::LEFT)
	{
		GetOwner()->Transform()->SetRelativePos(OGPos.x - 70.f, OGPos.y + 133.f, OGPos.z);
	}
	else if (BossScript->GetBossDir() == DIRECTION::RIGHT)
	{
		GetOwner()->Transform()->SetRelativePos(OGPos.x + 70.f, OGPos.y + 133.f, OGPos.z);
	}

	GetOwner()->Transform()->SetRelativeScale(700.f, 650.f, 10.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.35f, 0.41f, 0.f));
	GetOwner()->Collider2D()->SetOffset(Vec3(0.f, -0.23f, 0.f));

	GetOwner()->FlipBookComponent()->Play(5, 10, false);



	// 히트박스 (Wave) 생성
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	Ptr<qMaterial> pAlphaBlendMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DAlphaBlendMtrl");

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Player = pCurLevel->FindObjectByName(L"Player");

	Vec3 BossPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();

	BleedHitbox = new qGameObject;
	BleedHitbox->SetName(L"BleedHitbox");
	BleedHitbox->AddComponent(new qTransform);
	BleedHitbox->AddComponent(new qBleedScript);

	BleedHitbox->Transform()->SetRelativeScale(900.f, 400.f, 1.f);

	if (BossScript->GetBossDir() == DIRECTION::LEFT)
	{
		BleedHitbox->Transform()->SetRelativePos(Vec3(BossPos.x - 666.f, BossPos.y - 103.f, 20.f));
		BleedHitbox->Transform()->SetRelativeRotation(0.f, 3.141592f, 0.f);
	}
	else if (BossScript->GetBossDir() == DIRECTION::RIGHT)
	{
		BleedHitbox->Transform()->SetRelativePos(Vec3(BossPos.x + 666.f, BossPos.y - 103.f, 20.f));
	}

	BleedHitbox->AddComponent(new qMeshRender);
	BleedHitbox->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	BleedHitbox->MeshRender()->SetMaterial(pAlphaBlendMtrl);

	BleedHitbox->AddComponent(new qCollider2D);
	BleedHitbox->Collider2D()->SetScale(Vec3(0.f, 0.f, 0.f));

	BleedHitbox->AddComponent(new qFlipBookComponent);
	Ptr<qFlipBook> pBleedWave = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\boss_bleedwave.flip");
	BleedHitbox->FlipBookComponent()->AddFlipBook(0, pBleedWave);

	BleedHitbox->AddComponent(new qFSM);
	BleedHitbox->FSM()->AddState(L"BleedWave", new qBossBleedWaveState);

	BleedHitbox->FSM()->ChangeState(L"BleedWave");

	HitboxFlag = false;

	soundflag1 = false;
	soundflag2 = false;
	soundflag3 = false;
	soundflag4 = false;

}

void qBossBleedState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 0 && !soundflag1)
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\boss\\bleed1.wav", L"sound\\boss\\bleed1.wav");
		pSound->Play(1, 0.4, true);

		soundflag1 = true;
	}
	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 3 && !soundflag2)
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\boss\\bleedup.wav", L"sound\\boss\\bleedup.wav");
		pSound->Play(1, 0.4, true);

		soundflag2 = true;
	}
	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 8 && !soundflag3)
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\boss\\bleeddown.wav", L"sound\\boss\\bleeddown.wav");
		pSound->Play(1, 0.4, true);

		soundflag3 = true;
	}
	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 11 && !soundflag4)
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\boss\\wave.wav", L"sound\\boss\\wave.wav");
		pSound->Play(1, 0.5, true);

		soundflag4 = true;
	}


	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();


	// Index 맞춰서 히트박스 생성
	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 10 && !HitboxFlag)
	{
		pCurLevel->AddObject(8, BleedHitbox);
		HitboxFlag = true;
	}


	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"BossIdle");
		
		if (BleedHitbox != nullptr)
		{
			BleedHitbox->Destroy();
			BleedHitbox = nullptr;
			HitboxFlag = false;
		}
	}
}

void qBossBleedState::Exit()
{
	soundflag1 = false;
	soundflag2 = false;
	soundflag3 = false;
	soundflag4 = false;

	GetOwner()->Transform()->SetRelativePos(OGPos);
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);

	if (HitboxFlag)
		HitboxFlag = false;
}
