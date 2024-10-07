#include "pch.h"
#include "qBossSlamFistState.h"

#include <Scripts/qBossScript.h>


qBossSlamFistState::qBossSlamFistState()
	: qState((UINT)STATE_TYPE::BOSSSLAMFISTSTATE)
{
}

qBossSlamFistState::~qBossSlamFistState()
{
}

void qBossSlamFistState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(0, 18, false);
}

void qBossSlamFistState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 17)
	{
		GetOwner()->Collider2D()->SetScale(Vec3(0.75f, 0.35f, 1.f));
		GetOwner()->Collider2D()->SetOffset(Vec3(0.f, -0.26f, 0.f));
	}

	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		if (GetOwner() != nullptr)
		{
			GetOwner()->Destroy();
		}
		
	}

	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 24)
	{
		GetOwner()->Collider2D()->SetScale(Vec3(0.f, 0.f, 1.f));
	}
}

void qBossSlamFistState::Exit()
{
}
