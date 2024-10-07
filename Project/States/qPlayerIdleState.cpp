#include "pch.h"
#include "qPlayerIdleState.h"


#include <Scripts/qPlayerScript.h>

qPlayerIdleState::qPlayerIdleState()
	: qState((UINT)STATE_TYPE::PLAYERCOMBO1STATE)
	, WaitTime(0.f)
{
	
}

qPlayerIdleState::~qPlayerIdleState()
{

}

void qPlayerIdleState::Enter()
{
	qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();

	pPlayerScript->ResetCombo();

	GetOwner()->FlipBookComponent()->Play(0, 20, true);
}



void qPlayerIdleState::FinalTick()
{
	qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();

	if (KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT))
	{
		if (pPlayerScript->IsDirChanged() && GetOwner()->RigidBody()->IsGround() == true)
		{
			ChangeState(L"IdleUTurn");
		}
		else if(!pPlayerScript->IsDirChanged() && GetOwner()->RigidBody()->IsGround() == true)
		{
			ChangeState(L"IdleToRun");
		}
	}

	if (KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT))
	{
		if (pPlayerScript->IsDirChanged() && GetOwner()->RigidBody()->IsGround() == true)
		{
			ChangeState(L"IdleUTurn");
		}
		else if (!pPlayerScript->IsDirChanged() && GetOwner()->RigidBody()->IsGround() == true)
		{
			ChangeState(L"IdleToRun");
		}
	}

	if (KEY_TAP(KEY::SPACE))
	{
		ChangeState(L"Jump");
	}

	if (KEY_TAP(KEY::LSHIFT) && !(pPlayerScript->IsDashCoolTime()))
	{
		ChangeState(L"Dash");
	}

	if (KEY_TAP(KEY::S))
	{
		ChangeState(L"BookShoot");
	}

	if (KEY_TAP(KEY::D))
	{
		ChangeState(L"Crash");
	}

	if (KEY_TAP(KEY::F))
	{
		ChangeState(L"Range");
	}

	if (KEY_TAP(KEY::V))
	{
		ChangeState(L"ElevatorOut");
	}

	if (WaitTime < 5.f)
	{
		WaitTime += DT;
	}
	else
	{
		WaitTime = 0.f;
		ChangeState(L"Wait");
	}


}



void qPlayerIdleState::Exit()
{
}
