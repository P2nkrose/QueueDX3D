#include "pch.h"
#include "qPostOpenState.h"

#include <Engine/qFlipBookComponent.h>
#include <Engine/qGameObject.h>
#include <Scripts/qScriptMgr.h>
#include <Scripts/qPlayerScript.h>
#include <Scripts/qPostScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qPostOpenState::qPostOpenState()
	: qState((UINT)STATE_TYPE::POSTOPENSTATE)
{
}

qPostOpenState::~qPostOpenState()
{
}

void qPostOpenState::Enter()
{
	//qLevel* stage2 = qLevelMgr::GetInst()->GetLevelbyName(L"stage2");
	//qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	//qLevel* stageboss = qLevelMgr::GetInst()->GetLevelbyName(L"stageboss");
	//
	//if (pCurLevel == )
	//{
	//	GetOwner()->Transform()->SetRelativePos(Vec3(-4910.f, -40.f, 30.f));
	//	GetOwner()->Transform()->SetRelativeScale(Vec3(1600.f, 900.f, 0.f));
	//}
	//if (stageboss)
	//{
	//	GetOwner()->Transform()->SetRelativePos(Vec3(-390.f, -22.f, 30.f));
	//	GetOwner()->Transform()->SetRelativeScale(Vec3(1600.f, 900.f, 0.f));
	//}


	GetOwner()->FlipBookComponent()->Play(5, 20, false);
}

void qPostOpenState::FinalTick()
{
	static bool flag0 = false;
	static bool flag1 = false;
	static bool flag2 = false;

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();


	if (pCurLevel->GetName() == L"stage1" && GetOwner()->FlipBookComponent()->IsCurFlipBookFinished() && !flag0)
	{
		GetOwner()->Destroy();

		flag0 = true;
	}

	if (pCurLevel->GetName() == L"stage2" && GetOwner()->FlipBookComponent()->IsCurFlipBookFinished() && !flag1)
	{
		GetOwner()->Destroy();

		flag1 = true;
	}

	if (pCurLevel->GetName() == L"stageboss" && GetOwner()->FlipBookComponent()->IsCurFlipBookFinished() && !flag2)
	{
		GetOwner()->Destroy();

		flag2 = true;
	}


	
}

void qPostOpenState::Exit()
{

}
