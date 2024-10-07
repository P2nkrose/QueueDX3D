#include "pch.h"
#include "qBossUturnState.h"

#include <Scripts/qBossScript.h>

qBossUturnState::qBossUturnState()
	: qState((UINT)STATE_TYPE::BOSSUTURNSTATE)
{
}

qBossUturnState::~qBossUturnState()
{
}

void qBossUturnState::Enter()
{
	OGPos = GetOwner()->Transform()->GetRelativePos();
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativePos(OGPos.x, OGPos.y - 11.f, OGPos.z);
	GetOwner()->Collider2D()->SetScale(Vec3(0.5f, 0.9f, 0.f));
	GetOwner()->Collider2D()->SetOffset(Vec3(0.f, -0.02f, 0.f));

	GetOwner()->FlipBookComponent()->Play(9, 10, true);
}

void qBossUturnState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"BossIdle");
	}
}

void qBossUturnState::Exit()
{
	GetOwner()->Transform()->SetRelativePos(OGPos);
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);

	int PrevDir = (int)GetOwner()->GetScript<qBossScript>()->GetBossDir();
	GetOwner()->GetScript<qBossScript>()->SetBossDir((DIRECTION)-PrevDir);
}
