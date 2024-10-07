#include "pch.h"
#include "qDrownedUturnState.h"

#include <Scripts/qDrownedScript.h>

qDrownedUturnState::qDrownedUturnState()
	: qState((UINT)STATE_TYPE::DROWNEDUTURNSTATE)
{
}

qDrownedUturnState::~qDrownedUturnState()
{
}

void qDrownedUturnState::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(150.f, 230.f, 10.f);
	GetOwner()->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	GetOwner()->FlipBookComponent()->Play(2, 10, false);
}

void qDrownedUturnState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"DrownedIdle");
	}
}

void qDrownedUturnState::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);

	int PrevDir = (int)GetOwner()->GetScript<qDrownedScript>()->GetDrownedDir();

	GetOwner()->GetScript<qDrownedScript>()->SetDrownedDir((DIRECTION)-PrevDir);
}
