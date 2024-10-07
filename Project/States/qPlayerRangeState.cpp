#include "pch.h"
#include "qPlayerRangeState.h"

#include <Engine/qFlipBookComponent.h>
#include <Engine/qGameObject.h>
#include <Scripts/qPlayerScript.h>
#include <Scripts/qPlayerHitboxScript.h>
#include <Scripts/qRangeScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qPlayerRangeState::qPlayerRangeState()
	: qState((UINT)STATE_TYPE::PLAYERRANGESTATE)
{
}

qPlayerRangeState::~qPlayerRangeState()
{
}

void qPlayerRangeState::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(600.f, 600.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.22f, 0.22f, 0.f));

	GetOwner()->FlipBookComponent()->Play(20, 15, false);

	//qPlayerHitboxScript* HitboxScript = GetOwner()->GetChild(L"PlayerHitbox")->GetScript<qPlayerHitboxScript>();
	//if (HitboxScript != nullptr)
	//{
	//	HitboxScript->On();
	//}

	// 히트박스 생성
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	qGameObject* pPlayer = qLevelMgr::GetInst()->FindObjectByName(L"Player");
	qPlayerScript* pPlayerScript = pPlayer->GetScript<qPlayerScript>();
	Vec3 vPlayerPos = pPlayer->Transform()->GetRelativePos();
	
	RangeHitBox = new qGameObject;
	RangeHitBox->SetName(L"RangeHitBox");
	RangeHitBox->AddComponent(new qRangeScript);
	RangeHitBox->AddComponent(new qTransform);
	RangeHitBox->Transform()->SetRelativeScale(230.f, 260.f, 1.f);
	
	RangeHitBox->Transform()->SetRelativePos(Vec3(vPlayerPos.x, vPlayerPos.y + 60.f, vPlayerPos.z));
	
	
	RangeHitBox->AddComponent(new qCollider2D);
	RangeHitBox->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));



	soundflag = false;
}

void qPlayerRangeState::FinalTick()
{
	if (!soundflag)
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\player\\range3.wav", L"sound\\player\\range3.wav");
		pSound->Play(1, 0.5, true);

		soundflag = true;
	}


	static bool hitboxCreated = false; // 히트박스 생성 여부를 추적하는 플래그
	
	// 히트박스 생성
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	
	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 5 && !hitboxCreated)
	{
		pCurLevel->AddObject(4, RangeHitBox);
		hitboxCreated = true; // 히트박스가 생성되었음을 표시
	}

	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"Idle");

		if (RangeHitBox != nullptr)
		{
			RangeHitBox->Destroy();
			RangeHitBox = nullptr;
			hitboxCreated = false;	// 다음 상태 전환 시를 위해 플래그 초기화
		}
	}


}

void qPlayerRangeState::Exit()
{
	soundflag = false;

	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
