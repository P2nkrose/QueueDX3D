#include "pch.h"
#include "qElevatorCloseState.h"

#include <Scripts/qElevatorScript.h>
#include <Scripts/qPlayerScript.h>

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qElevatorCloseState::qElevatorCloseState()
	: qState((UINT)STATE_TYPE::ELEVATORCLOSESTATE)
{
}

qElevatorCloseState::~qElevatorCloseState()
{
}

void qElevatorCloseState::Enter()
{

	GetOwner()->FlipBookComponent()->Play(8, 15, false);
}

void qElevatorCloseState::FinalTick()
{
	static bool flag = false;

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished() && !flag)
	{
		if (pCurLevel->GetName() == L"stage2")
		{
			qGameObject* pPost = pCurLevel->FindObjectByName(L"PostClose");
			pPost->FSM()->ChangeState(L"PostClose");

			flag = true;
		}
	}



	static bool flagclose = false;

	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 26 && !flagclose)
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\transfer\\eleclosedown.wav", L"sound\\transfer\\eleclosedown.wav");
		pSound->Play(1, 0.5, true);

		flagclose = true;
	}
	
}

void qElevatorCloseState::Exit()
{
}
