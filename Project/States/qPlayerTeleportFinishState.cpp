#include "pch.h"
#include "qPlayerTeleportFinishState.h"

#include <Engine/qFlipBookComponent.h>
#include <Engine/qGameObject.h>
#include <Scripts/qPlayerScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qPlayerTeleportFinishState::qPlayerTeleportFinishState()
	: qState((UINT)STATE_TYPE::PLAYERTELEPORTFINISHSTATE)
{
}

qPlayerTeleportFinishState::~qPlayerTeleportFinishState()
{
}

void qPlayerTeleportFinishState::Enter()
{

	OGPos = GetOwner()->Transform()->GetRelativePos();
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	//OGColScale = GetOwner()->Collider2D()->GetScale();

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	if (pCurLevel->GetName() == L"stage1")
	{
		GetOwner()->Transform()->SetRelativePos(875.f, -484.f, 10.f);
		GetOwner()->Transform()->SetRelativeScale(0.01f, 0.01f, 0.f);
	}
	
	

	
	//GetOwner()->Collider2D()->SetScale(Vec3(0.5f, 0.5f, 0.f));

	GetOwner()->FlipBookComponent()->Play(23, 15, false);

}

void qPlayerTeleportFinishState::FinalTick()
{
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	static bool flag = false;

	if (pCurLevel->GetName() == L"stage2" && !flag)
	{
		GetOwner()->RigidBody()->SetGround(true);
		GetOwner()->Transform()->SetRelativeScale(0.01f, 0.01f, 0.f);
		GetOwner()->Transform()->SetRelativePos(5207.f, -227.f, 10.f);

		flag = true;
	}


	//static bool flag = false;

	//qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	//if (pCurLevel->GetName() == L"stage1" && !flag)
	//{
	//	GetOwner()->Transform()->SetRelativePos(875.f, -484.f, 10.f);
	//	GetOwner()->Transform()->SetRelativeScale(0.01f, 0.01f, 0.f);
	//	flag = true;
	//}
	//if (pCurLevel->GetName() == L"stage2" && !flag)
	//{
	//	GetOwner()->RigidBody()->SetGround(true);
	//	GetOwner()->Transform()->SetRelativePos(-4910.f, -200.f, 10.f);
	//	GetOwner()->Transform()->SetRelativeScale(0.01f, 0.01f, 0.f);
	//	flag = true;
	//}

}

void qPlayerTeleportFinishState::Exit()
{
	GetOwner()->Transform()->SetRelativePos(OGPos);
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	//GetOwner()->Collider2D()->SetScale(OGColScale);
}
