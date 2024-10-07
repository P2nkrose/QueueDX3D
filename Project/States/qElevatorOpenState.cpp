#include "pch.h"
#include "qElevatorOpenState.h"

#include <Scripts/qElevatorScript.h>
#include <Scripts/qPlayerScript.h>

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qElevatorOpenState::qElevatorOpenState()
	: qState((UINT)STATE_TYPE::ELEVATOROPENSTATE)
{
}

qElevatorOpenState::~qElevatorOpenState()
{
}

void qElevatorOpenState::Enter()
{

	GetOwner()->FlipBookComponent()->Play(7, 15, false);

}

void qElevatorOpenState::FinalTick()
{


	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	if (pCurLevel->GetName() == L"stage2")
	{
		static bool flag1 = false;
		static bool flag2 = false;

		if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 10 && !flag1)
		{
			Ptr<qSound> pSoundEleOpen = qAssetMgr::GetInst()->Load<qSound>(L"sound\\transfer\\eleopenup.wav", L"sound\\transfer\\eleopenup.wav");
			pSoundEleOpen->Play(1, 0.8, true);

			flag1 = true;
		}

		if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 34 && !flag2)
		{
			Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\transfer\\eleopendoor.wav", L"sound\\transfer\\eleopendoor.wav");
			pSound->Play(1, 0.5, true);

			flag2 = true;
		}
	}

	if (pCurLevel->GetName() == L"stageboss")
	{
		static bool flag3 = false;
		static bool flag4 = false;

		if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 10 && !flag3)
		{
			Ptr<qSound> pSoundEleOpen = qAssetMgr::GetInst()->Load<qSound>(L"sound\\transfer\\eleopenup.wav", L"sound\\transfer\\eleopenup.wav");
			pSoundEleOpen->Play(1, 0.8, true);

			flag3 = true;
		}

		if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 34 && !flag4)
		{
			Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\transfer\\eleopendoor.wav", L"sound\\transfer\\eleopendoor.wav");
			pSound->Play(1, 0.5, true);

			flag4 = true;
		}
	}



	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"ElevatorStay");
	}

}

void qElevatorOpenState::Exit()
{
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	if (pCurLevel->GetName() == L"stage2")
	{
		//Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\transfer\\eleopendoor.wav", L"sound\\transfer\\eleopendoor.wav");
		//pSound->Play(1, 0.5, true);

		qGameObject* pPlayer = qLevelMgr::GetInst()->FindObjectByName(L"Player");
		pPlayer->FSM()->ChangeState(L"ElevatorOut");
	}
	if (pCurLevel->GetName() == L"stageboss")
	{
		//Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\transfer\\eleopendoor.wav", L"sound\\transfer\\eleopendoor.wav");
		//pSound->Play(1, 0.5, true);

		qGameObject* pPlayer = qLevelMgr::GetInst()->FindObjectByName(L"Player");
		pPlayer->FSM()->ChangeState(L"ElevatorOut");
	}

}
