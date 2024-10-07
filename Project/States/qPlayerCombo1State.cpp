#include "pch.h"
#include "qPlayerCombo1State.h"

#include <Engine/qGameObject.h>
#include <Scripts/qPlayerScript.h>
#include <Scripts/qComboScript.h>
#include <Scripts/qPlayerHitboxScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qPlayerCombo1State::qPlayerCombo1State()
	: qState((UINT)STATE_TYPE::PLAYERCOMBO1STATE)
	, Combo1HitBox(nullptr)

{


} 

qPlayerCombo1State::~qPlayerCombo1State()
{
}

void qPlayerCombo1State::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(550.f, 550.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.24f, 0.24f, 0.f));

	GetOwner()->FlipBookComponent()->Play(13, 15, false);

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
	
	Combo1HitBox = new qGameObject;
	Combo1HitBox->SetName(L"Combo1HitBox");
	Combo1HitBox->AddComponent(new qComboScript);
	Combo1HitBox->AddComponent(new qTransform);
	Combo1HitBox->Transform()->SetRelativeScale(220.f, 100.f, 1.f);
	
	if (pPlayerScript->GetPlayerDir() == DIRECTION::LEFT)
	{
		Combo1HitBox->Transform()->SetRelativePos(Vec3(vPlayerPos.x - 160.f, vPlayerPos.y, vPlayerPos.z));
	}
	else if (pPlayerScript->GetPlayerDir() == DIRECTION::RIGHT)
	{
		Combo1HitBox->Transform()->SetRelativePos(Vec3(vPlayerPos.x + 160.f, vPlayerPos.y, vPlayerPos.z));
	}
	
	Combo1HitBox->AddComponent(new qCollider2D);
	Combo1HitBox->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	pCurLevel->AddObject(4, Combo1HitBox);


}

void qPlayerCombo1State::FinalTick()
{


	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		if (KEY_TAP(KEY::A))
		{
			ChangeState(L"Combo2");
		}
		else
		{
			ChangeState(L"Idle");
		}
	}
}

void qPlayerCombo1State::Exit()
{

	Combo1HitBox->Destroy();
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
