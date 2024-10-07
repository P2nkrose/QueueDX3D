#include "pch.h"
#include "qLogoState.h"

#include <Engine/qFlipBookComponent.h>
#include <Engine/qGameObject.h>
#include <Scripts/qScriptMgr.h>
#include <Scripts/qPostScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qLogoState::qLogoState()
	: qState((UINT)STATE_TYPE::LOGOSTATE)
{
}

qLogoState::~qLogoState()
{
}

void qLogoState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(1, 10, false);
}

void qLogoState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		qLevel* pLoading1 = qLevelMgr::GetInst()->GetLevelbyName(L"loading1");

		ChangeLevel(pLoading1, LEVEL_STATE::PLAY);
	}
}

void qLogoState::Exit()
{
}
