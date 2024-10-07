#include "pch.h"
#include "qPlayerCrashState.h"

#include <Engine/qFlipBookComponent.h>
#include <Engine/qGameObject.h>
#include <Scripts/qPlayerScript.h>
#include <Scripts/qPlayerHitboxScript.h>
#include <Scripts/qCrashScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qPlayerCrashState::qPlayerCrashState()
	: qState((UINT)STATE_TYPE::PLAYERCRASHSTATE)
{
}

qPlayerCrashState::~qPlayerCrashState()
{
}

void qPlayerCrashState::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(550.f, 550.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.237f, 0.237f, 0.f));

	GetOwner()->FlipBookComponent()->Play(19, 15, false);

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
	
	CrashHitBox = new qGameObject;
	CrashHitBox->SetName(L"CrashHitBox");
	CrashHitBox->AddComponent(new qCrashScript);
	CrashHitBox->AddComponent(new qTransform);
	CrashHitBox->Transform()->SetRelativeScale(190.f, 100.f, 1.f);
	
	if (pPlayerScript->GetPlayerDir() == DIRECTION::LEFT)
	{
		CrashHitBox->Transform()->SetRelativePos(Vec3(vPlayerPos.x - 155.f, vPlayerPos.y, vPlayerPos.z));
	}
	else if (pPlayerScript->GetPlayerDir() == DIRECTION::RIGHT)
	{
		CrashHitBox->Transform()->SetRelativePos(Vec3(vPlayerPos.x + 155.f, vPlayerPos.y, vPlayerPos.z));
	}
	
	CrashHitBox->AddComponent(new qCollider2D);
	CrashHitBox->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	pCurLevel->AddObject(4, CrashHitBox);

	soundflag = false;
}

void qPlayerCrashState::FinalTick()
{
	if (!soundflag)
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\player\\crash.wav", L"sound\\player\\crash.wav");
		pSound->Play(1, 0.5, true);

		soundflag = true;
	}

	



	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"Idle");
	}
}

void qPlayerCrashState::Exit()
{
	soundflag = false;

	CrashHitBox->Destroy();
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
