#include "pch.h"
#include "qGhostUturnState.h"

#include <Scripts/qGhostScript.h>

qGhostUturnState::qGhostUturnState()
	: qState((UINT)STATE_TYPE::GHOSTUTURNSTATE)
{
}

qGhostUturnState::~qGhostUturnState()
{
}

void qGhostUturnState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(2, 10, false);
}

void qGhostUturnState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"GhostIdle");
	}
}

void qGhostUturnState::Exit()
{
	int PrevDir = (int)GetOwner()->GetScript<qGhostScript>()->GetGhostDir();

	GetOwner()->GetScript<qGhostScript>()->SetGhostDir((DIRECTION)-PrevDir);
}
