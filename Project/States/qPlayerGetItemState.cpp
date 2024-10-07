#include "pch.h"
#include "qPlayerGetItemState.h"

#include <Engine/qScript.h>

qPlayerGetItemState::qPlayerGetItemState()
	: qState((UINT)STATE_TYPE::PLAYERGETITEMSTATE)
{
}

qPlayerGetItemState::~qPlayerGetItemState()
{
}

void qPlayerGetItemState::Enter()
{
	OGPos = GetOwner()->Transform()->GetRelativePos();
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();


	GetOwner()->Transform()->SetRelativeScale(300.f, 400.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.43333f, 0.325f, 0.f));

	GetOwner()->FlipBookComponent()->Play(12, 13, true);
}

void qPlayerGetItemState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"Idle");
	}
}

void qPlayerGetItemState::Exit()
{
	//GetOwner()->Transform()->SetRelativePos(OGPos);
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
