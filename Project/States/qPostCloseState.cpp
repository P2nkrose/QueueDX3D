#include "pch.h"
#include "qPostCloseState.h"

#include <Engine/qFlipBookComponent.h>
#include <Engine/qGameObject.h>
#include <Scripts/qScriptMgr.h>
#include <Scripts/qPlayerScript.h>
#include <Scripts/qPostScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>
#include <Engine/qAsset.h>
#include <Engine/qAssetMgr.h>
#include <Engine/qSound.h>

qPostCloseState::qPostCloseState()
	: qState((UINT)STATE_TYPE::POSTCLOSESTATE)
{
}

qPostCloseState::~qPostCloseState()
{
}

void qPostCloseState::Enter()
{
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	if (pCurLevel->GetName() == L"title")
	{
		GetOwner()->Transform()->SetRelativePos(Vec3(0.f, 0.f, 10.f));
		GetOwner()->Transform()->SetRelativeScale(Vec3(1600.f, 900.f, 0.f));

		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\background\\title.wav", L"sound\\background\\title.wav");
		pSound->Stop();
	}
	if (pCurLevel->GetName() == L"stage1")
	{
		GetOwner()->Transform()->SetRelativePos(Vec3(474.f, -120.f, 10.f));
		GetOwner()->Transform()->SetRelativeScale(Vec3(1600.f, 900.f, 0.f));
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\background\\stage1.wav", L"sound\\background\\stage1.wav");
		pSound->Stop();
	}
	if (pCurLevel->GetName() == L"stage2")
	{
		// 레벨2 close시 위치 설정
		GetOwner()->Transform()->SetRelativePos(Vec3(4926.f, 100.f, 10.f));
		GetOwner()->Transform()->SetRelativeScale(Vec3(1600.f, 900.f, 0.f));
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\background\\stage2.wav", L"sound\\background\\stage2.wav");
		pSound->Stop();
	}

	Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\transfer\\postclose.wav", L"sound\\transfer\\postclose.wav");
	pSound->Play(1, 0.8, true);

	GetOwner()->FlipBookComponent()->Play(4, 15, false);
}

void qPostCloseState::FinalTick()
{

	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		qLevel* pStage1 = qLevelMgr::GetInst()->GetLevelbyName(L"stage1");
		qLevel* pStage2 = qLevelMgr::GetInst()->GetLevelbyName(L"stage2");
		qLevel* pStageBoss = qLevelMgr::GetInst()->GetLevelbyName(L"stageboss");
		qLevel* pLoading = qLevelMgr::GetInst()->GetLevelbyName(L"loading");

		qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

		if (pCurLevel->GetName() == L"title")
		{
			ChangeLevel(pLoading, LEVEL_STATE::PLAY);
		}
		if (pCurLevel->GetName() == L"stage1")
		{
			ChangeLevel(pStage2, LEVEL_STATE::PLAY);
		}
		if (pCurLevel->GetName() == L"stage2")
		{
			ChangeLevel(pStageBoss, LEVEL_STATE::PLAY);

		}
	}

	
}

void qPostCloseState::Exit()
{


	//qLevel* pStage1 = qLevelMgr::GetInst()->GetLevelbyName(L"stage1");
	//qLevel* pStage2 = qLevelMgr::GetInst()->GetLevelbyName(L"stage2");

	//qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	//if (pCurLevel->GetName() == L"stage1")
	//{
	//	ChangeLevel(pStage2, LEVEL_STATE::PLAY);
	//}
	//else if (pCurLevel->GetName() == L"stage2")
	//{
	//	//ChangeLevel(pBoss, LEVEL_STATE::PLAY);
	//}
}
