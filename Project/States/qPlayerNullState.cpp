#include "pch.h"
#include "qPlayerNullState.h"

#include <Engine/qFlipBookComponent.h>
#include <Engine/qGameObject.h>
#include <Scripts/qPlayerScript.h>
#include <Engine/qRigidBody.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qPlayerNullState::qPlayerNullState()
	: qState((UINT)STATE_TYPE::PLAYERNULLSTATE)
{
}

qPlayerNullState::~qPlayerNullState()
{
}

void qPlayerNullState::Enter()
{
	OGPos = GetOwner()->Transform()->GetRelativePos();
	OGScale = GetOwner()->Transform()->GetRelativeScale();

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	if (pCurLevel->GetName() == L"stage2")
	{
		GetOwner()->RigidBody()->SetGround(true);
		GetOwner()->Transform()->SetRelativePos(-4910.f, -200.f, 10.f);
		GetOwner()->Transform()->SetRelativeScale(0.01f, 0.01f, 0.f);

	}
	if (pCurLevel->GetName() == L"stageboss")
	{
		GetOwner()->RigidBody()->SetGround(true);
		GetOwner()->Transform()->SetRelativePos(-650.f, -337.f, 10.f);
		GetOwner()->Transform()->SetRelativeScale(0.01f, 0.01f, 0.f);

	}


	GetOwner()->FlipBookComponent()->Play(25, 15, false);
}

void qPlayerNullState::FinalTick()
{
}

void qPlayerNullState::Exit()
{
	GetOwner()->Transform()->SetRelativePos(OGPos);
	GetOwner()->Transform()->SetRelativeScale(OGScale);
}
