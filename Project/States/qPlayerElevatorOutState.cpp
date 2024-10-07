#include "pch.h"
#include "qPlayerElevatorOutState.h"

#include <Scripts/qPlayerScript.h>

qPlayerElevatorOutState::qPlayerElevatorOutState()
	: qState((UINT)STATE_TYPE::PLAYERELEVATOROUTSTATE)
{
}

qPlayerElevatorOutState::~qPlayerElevatorOutState()
{
}

void qPlayerElevatorOutState::Enter()
{

	GetOwner()->FlipBookComponent()->Play(11, 15, true);
}

void qPlayerElevatorOutState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"Idle");
	}
}

void qPlayerElevatorOutState::Exit()
{
}
