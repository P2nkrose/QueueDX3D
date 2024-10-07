#include "pch.h"
#include "qDeathSoulState.h"

qDeathSoulState::qDeathSoulState()
	: qState((UINT)STATE_TYPE::DEATHSOULSTATE)
{
}

qDeathSoulState::~qDeathSoulState()
{
}

void qDeathSoulState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(0, 10, false);
}

void qDeathSoulState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		GetOwner()->Destroy();
	}
}

void qDeathSoulState::Exit()
{
}
