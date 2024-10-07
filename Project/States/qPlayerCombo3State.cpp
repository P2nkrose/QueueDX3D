#include "pch.h"
#include "qPlayerCombo3State.h"

#include <Engine/qGameObject.h>
#include <Scripts/qPlayerScript.h>
#include <Scripts/qPlayerHitboxScript.h>
#include <Scripts/qComboScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qPlayerCombo3State::qPlayerCombo3State()
	: qState((UINT)STATE_TYPE::PLAYERCOMBO3STATE)

{
}

qPlayerCombo3State::~qPlayerCombo3State()
{
}

void qPlayerCombo3State::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(650.f, 650.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.2f, 0.2f, 0.f));

	GetOwner()->FlipBookComponent()->Play(15, 15, false);


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
	
	Combo3HitBox = new qGameObject;
	Combo3HitBox->SetName(L"Combo3HitBox");
	Combo3HitBox->AddComponent(new qComboScript);
	Combo3HitBox->AddComponent(new qTransform);
	Combo3HitBox->Transform()->SetRelativeScale(320.f, 90.f, 1.f);
	
	if (pPlayerScript->GetPlayerDir() == DIRECTION::LEFT)
	{
		Combo3HitBox->Transform()->SetRelativePos(Vec3(vPlayerPos.x - 100.f, vPlayerPos.y + 15.f, vPlayerPos.z));
	}
	else if (pPlayerScript->GetPlayerDir() == DIRECTION::RIGHT)
	{
		Combo3HitBox->Transform()->SetRelativePos(Vec3(vPlayerPos.x + 100.f, vPlayerPos.y + 15.f, vPlayerPos.z));
	}
	
	Combo3HitBox->AddComponent(new qCollider2D);
	Combo3HitBox->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	pCurLevel->AddObject(4, Combo3HitBox);

}

void qPlayerCombo3State::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"Idle");
	}

}

void qPlayerCombo3State::Exit()
{


	Combo3HitBox->Destroy();
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
