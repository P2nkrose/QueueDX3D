#include "pch.h"
#include "qLoadingState.h"

#include <Engine/qFlipBookComponent.h>
#include <Engine/qGameObject.h>
#include <Scripts/qScriptMgr.h>
#include <Scripts/qPostScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qLoadingState::qLoadingState()
	: qState((UINT)STATE_TYPE::LOADINGSTATE)
{
}

qLoadingState::~qLoadingState()
{
}

void qLoadingState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(1, 10, false);
}

void qLoadingState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		qLevel* pStage1 = qLevelMgr::GetInst()->GetLevelbyName(L"stage1");
		
		ChangeLevel(pStage1, LEVEL_STATE::PLAY);

		// Sound
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\background\\stage1.wav", L"sound\\background\\stage1.wav");
		pSound->Play(0, 0.7, true);
	}
}

void qLoadingState::Exit()
{
}
