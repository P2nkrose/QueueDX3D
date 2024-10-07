#include "pch.h"
#include "qBookEffectState.h"

qBookEffectState::qBookEffectState()
	: qState((UINT)STATE_TYPE::BOOKEFFECTSTATE)
{
}

qBookEffectState::~qBookEffectState()
{
}

void qBookEffectState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(0, 10, true);
}

void qBookEffectState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		GetOwner()->Destroy();
	}
}

void qBookEffectState::Exit()
{
}
