#include "pch.h"
#include "qBossIntroState.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include <Scripts/qBossScript.h>
#include <Scripts/qCameraMoveScript.h>

qBossIntroState::qBossIntroState()
	: qState((UINT)STATE_TYPE::BOSSINTROSTATE)
{
}

qBossIntroState::~qBossIntroState()
{
}

void qBossIntroState::Enter()
{
	OGPos = GetOwner()->Transform()->GetRelativePos();
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativePos(OGPos.x, OGPos.y - 11.f, OGPos.z);
	GetOwner()->Collider2D()->SetScale(Vec3(0.f, 0.f, 0.f));
	GetOwner()->Collider2D()->SetOffset(Vec3(0.f, 0.04f, 0.f));

	GetOwner()->FlipBookComponent()->Play(0, 10, true);
}

void qBossIntroState::FinalTick()
{
	static bool flag1 = false;
	static bool flag2 = false;


	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 5 && !flag1)
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\boss\\intro1.wav", L"sound\\boss\\intro1.wav");
		pSound->Play(1, 0.5, true);

		flag1 = true;
	}

	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 55 && !flag2)
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\boss\\intro2.wav", L"sound\\boss\\intro2.wav");
		pSound->Play(1, 0.5, true);

		flag2 = true;
	}



	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"BossIdle");
	}
}

void qBossIntroState::Exit()
{
	GetOwner()->Transform()->SetRelativePos(OGPos);
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Camera = pCurLevel->FindObjectByName(L"MainCamera");

	qCameraMoveScript* CameraScript = Camera->GetScript<qCameraMoveScript>();
	CameraScript->SetClap(false);
}
