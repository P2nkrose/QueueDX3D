#include "pch.h"
#include "qPlayerCombo2State.h"

#include <Engine/qGameObject.h>
#include <Scripts/qPlayerScript.h>
#include <Scripts/qPlayerHitboxScript.h>
#include <Scripts/qComboScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qPlayerCombo2State::qPlayerCombo2State()
	: qState((UINT)STATE_TYPE::PLAYERCOMBO2STATE)
	, Combo2HitBox(nullptr)

{
}

qPlayerCombo2State::~qPlayerCombo2State()
{
}

void qPlayerCombo2State::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(550.f, 550.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.24f, 0.24f, 0.f));

	GetOwner()->FlipBookComponent()->Play(14, 15, false);

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
	
	Combo2HitBox = new qGameObject;
	Combo2HitBox->SetName(L"Combo2HitBox");
	Combo2HitBox->AddComponent(new qComboScript);
	Combo2HitBox->AddComponent(new qTransform);
	Combo2HitBox->Transform()->SetRelativeScale(170.f, 230.f, 1.f);
	
	if (pPlayerScript->GetPlayerDir() == DIRECTION::LEFT)
	{
		Combo2HitBox->Transform()->SetRelativePos(Vec3(vPlayerPos.x - 60.f, vPlayerPos.y + 50.f, vPlayerPos.z));
	}
	else if (pPlayerScript->GetPlayerDir() == DIRECTION::RIGHT)
	{
		Combo2HitBox->Transform()->SetRelativePos(Vec3(vPlayerPos.x + 60.f, vPlayerPos.y + 50.f, vPlayerPos.z));
	}
	
	Combo2HitBox->AddComponent(new qCollider2D);
	Combo2HitBox->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	pCurLevel->AddObject(4, Combo2HitBox);


}

void qPlayerCombo2State::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		if (KEY_TAP(KEY::A))
		{
			ChangeState(L"Combo3");
		}
		else
		{
			ChangeState(L"Idle");
		}
	}


}

void qPlayerCombo2State::Exit()
{

	Combo2HitBox->Destroy();
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
