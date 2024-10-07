#include "pch.h"
#include "qPortalScript.h"

#include "qPlayerScript.h"
#include "qMissileScript.h"
#include "qBookScript_Left.h"
#include "qBookScript_Right.h"
#include "qComboScript.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>
#include <Engine/qRigidBody.h>
#include <Engine/qScript.h>
#include <Engine/qState.h>

#include <States/qStateMgr.h>
#include <Engine/qStateMachine.h>

qPortalScript::qPortalScript()
	: qScript(UINT(SCRIPT_TYPE::PORTALSCRIPT))
{
}

qPortalScript::~qPortalScript()
{
}

void qPortalScript::Begin()
{
}

void qPortalScript::Tick()
{
}

void qPortalScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{

}

void qPortalScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	//qLevel* pStage1 = qLevelMgr::GetInst()->GetLevelbyName(L"stage1");
	//qLevel* pStage2 = qLevelMgr::GetInst()->GetLevelbyName(L"stage2");
	//qLevel* pBoss = qLevelMgr::GetInst()->GetLevelbyName(L"boss");
	//
	//qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	//
	//if (_OtherObject->GetName() == L"Player")
	//{
	//	if (pCurLevel->GetName() == L"stage1")
	//	{
	//		ChangeLevel(pStage2, LEVEL_STATE::PLAY);
	//	}
	//	else if (pCurLevel->GetName() == L"stage2")
	//	{
	//		ChangeLevel(pBoss, LEVEL_STATE::PLAY);
	//	}
	//}
}

void qPortalScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qPortalScript::SaveToFile(FILE* _File)
{
}

void qPortalScript::LoadFromFile(FILE* _File)
{
}
