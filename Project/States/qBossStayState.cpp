#include "pch.h"
#include "qBossStayState.h"

#include <Scripts/qBossScript.h>

qBossStayState::qBossStayState()
	: qState((UINT)STATE_TYPE::BOSSSTAYSTATE)
{
}

qBossStayState::~qBossStayState()
{
}

void qBossStayState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(8, 10, true);
}

void qBossStayState::FinalTick()
{
}

void qBossStayState::Exit()
{
}
