#include "pch.h"
#include "qWarningState.h"

qWarningState::qWarningState()
	: qState((UINT)STATE_TYPE::WARNINGSTATE)
{
}

qWarningState::~qWarningState()
{
}

void qWarningState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(0, 10, false);
}

void qWarningState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		GetOwner()->Destroy();
	}
}

void qWarningState::Exit()
{
}
