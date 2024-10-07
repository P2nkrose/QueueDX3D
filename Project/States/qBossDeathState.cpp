#include "pch.h"
#include "qBossDeathState.h"

#include <Scripts/qBossScript.h>

qBossDeathState::qBossDeathState()
	: qState((UINT)STATE_TYPE::BOSSDEATHSTATE)
{
}

qBossDeathState::~qBossDeathState()
{
}

void qBossDeathState::Enter()
{
	OGPos = GetOwner()->Transform()->GetRelativePos();
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativePos(OGPos.x, OGPos.y + 58.f, OGPos.z);
	GetOwner()->Transform()->SetRelativeScale(690.f, 480.f, 10.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.0f, 0.0f, 0.f));

	GetOwner()->FlipBookComponent()->Play(7, 10, false);


	soundflag = false;

}

void qBossDeathState::FinalTick()
{
	if (!soundflag)
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\boss\\death.wav", L"sound\\boss\\death.wav");
		pSound->Play(1, 0.7, true);

		soundflag = true;
	}



	static bool flag = false;

	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished() && !flag)
	{
		// µ¥½º ¼ÕÅ¹Å¹ (½Ã°£³²À¸¸é)



	}
}

void qBossDeathState::Exit()
{
	soundflag = false;

	GetOwner()->Transform()->SetRelativePos(OGPos);
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
