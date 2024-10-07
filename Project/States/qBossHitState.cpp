#include "pch.h"
#include "qBossHitState.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include <Scripts/qBossScript.h>

qBossHitState::qBossHitState()
	: qState((UINT)STATE_TYPE::BOSSHITSTATE)
	, m_BossBumpSpeed(100.f)
	, m_MaxRange(0.f)
{
}

qBossHitState::~qBossHitState()
{
}

void qBossHitState::Enter()
{
	OGPos = GetOwner()->Transform()->GetRelativePos();
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	qBossScript* BossScript = GetOwner()->GetScript<qBossScript>();
	if (BossScript->GetBossDir() == DIRECTION::LEFT)
	{
		GetOwner()->Transform()->SetRelativePos(OGPos.x - 22.f, OGPos.y + 19.f, OGPos.z);
	}
	else if (BossScript->GetBossDir() == DIRECTION::RIGHT)
	{
		GetOwner()->Transform()->SetRelativePos(OGPos.x + 22.f, OGPos.y + 19.f, OGPos.z);
	}

	
	GetOwner()->Transform()->SetRelativeScale(520.f, 400.f, 10.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.48f, 0.675f, 0.f));
	GetOwner()->Collider2D()->SetOffset(Vec3(0.08f, -0.09f, 0.f));

	GetOwner()->FlipBookComponent()->Play(6, 10, false);


	

}

void qBossHitState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"BossIdle");
	}
}

void qBossHitState::Exit()
{
	GetOwner()->Transform()->SetRelativePos(OGPos);
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
