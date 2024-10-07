#include "pch.h"
#include "qPlayerCombo4State.h"

#include <Engine/qFlipBookComponent.h>
#include <Engine/qGameObject.h>
#include <Scripts/qPlayerScript.h>
#include <Scripts/qPlayerHitboxScript.h>
#include <Scripts/qComboScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qPlayerCombo4State::qPlayerCombo4State()
	: qState((UINT)STATE_TYPE::PLAYERCOMBO4STATE)
	, Combo4HitBox(nullptr)

{
}

qPlayerCombo4State::~qPlayerCombo4State()
{
}

void qPlayerCombo4State::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(700.f, 700.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.187f, 0.187f, 0.f));

	GetOwner()->FlipBookComponent()->Play(16, 15, false);

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
	
	
	
	Combo4HitBox = new qGameObject;
	Combo4HitBox->SetName(L"Combo4HitBox");
	Combo4HitBox->AddComponent(new qComboScript);
	Combo4HitBox->AddComponent(new qTransform);
	Combo4HitBox->Transform()->SetRelativeScale(230.f, 230.f, 1.f);
	
	if (pPlayerScript->GetPlayerDir() == DIRECTION::LEFT)
	{
		Combo4HitBox->Transform()->SetRelativePos(Vec3(vPlayerPos.x - 180.f, vPlayerPos.y + 50.f, vPlayerPos.z));
	}
	else if (pPlayerScript->GetPlayerDir() == DIRECTION::RIGHT)
	{
		Combo4HitBox->Transform()->SetRelativePos(Vec3(vPlayerPos.x + 180.f, vPlayerPos.y + 50.f, vPlayerPos.z));
	}
	
	Combo4HitBox->AddComponent(new qCollider2D);
	Combo4HitBox->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));


}

void qPlayerCombo4State::FinalTick()
{
	static bool hitboxCreated = false; // 히트박스 생성 여부를 추적하는 플래그

	// 히트박스 생성
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	
	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 9 && !hitboxCreated)
	{
		pCurLevel->AddObject(4, Combo4HitBox);
		hitboxCreated = true; // 히트박스가 생성되었음을 표시
	}

	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"Idle");
		
		if (Combo4HitBox != nullptr)
		{
			Combo4HitBox->Destroy();
			Combo4HitBox = nullptr;
			hitboxCreated = false; // 다음 상태 전환 시를 위해 플래그 초기화
		}

	}


}

void qPlayerCombo4State::Exit()
{



	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
