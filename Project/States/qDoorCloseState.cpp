#include "pch.h"
#include "qDoorCloseState.h"

qDoorCloseState::qDoorCloseState()
	: qState((UINT)STATE_TYPE::DOORCLOSESTATE)
{
}

qDoorCloseState::~qDoorCloseState()
{
}

void qDoorCloseState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(3, 10, false);
}

void qDoorCloseState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"DoorStay");
	}
}

void qDoorCloseState::Exit()
{
}
