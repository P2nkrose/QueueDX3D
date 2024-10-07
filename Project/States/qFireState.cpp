#include "pch.h"
#include "qFireState.h"

qFireState::qFireState()
	: qState((UINT)STATE_TYPE::FIRESTATE)
{
}

qFireState::~qFireState()
{
}

void qFireState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(0, 17, false);
}

void qFireState::FinalTick()
{
}

void qFireState::Exit()
{
}
