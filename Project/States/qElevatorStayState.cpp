#include "pch.h"
#include "qElevatorStayState.h"

#include <Scripts/qElevatorScript.h>
#include <Scripts/qPlayerScript.h>

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qElevatorStayState::qElevatorStayState()
	: qState((UINT)STATE_TYPE::ELEVATORSTAYSTATE)
{
}

qElevatorStayState::~qElevatorStayState()
{
}

void qElevatorStayState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(6, 15, true);
}

void qElevatorStayState::FinalTick()
{

}

void qElevatorStayState::Exit()
{
}
