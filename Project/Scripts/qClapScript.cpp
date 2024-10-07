#include "pch.h"
#include "qClapScript.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>
#include "qCameraMoveScript.h"

qClapScript::qClapScript()
	: qScript((UINT)SCRIPT_TYPE::CLAPSCRIPT)
{
}

qClapScript::~qClapScript()
{
}

void qClapScript::Begin()
{
}

void qClapScript::Tick()
{
}

void qClapScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Camera = pCurLevel->FindObjectByName(L"MainCamera");
	qGameObject* Boss = pCurLevel->FindObjectByName(L"Boss");

	if (GetOwner() != nullptr)
	{
		if (_OtherObject->GetName() == L"Player")
		{
			qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

			qGameObject* Warning = pCurLevel->FindObjectByName(L"Warning");
			
			Warning->Transform()->SetRelativeScale(1600.f, 900.f, 1.f);
			Warning->FSM()->ChangeState(L"WarningFlip");


			qGameObject* bossUI = pCurLevel->FindObjectByName(L"bossUI");
			bossUI->Transform()->SetRelativeScale(1600.f, 900.f, 1.f);

			qGameObject* bossHUD = pCurLevel->FindObjectByName(L"BossHUD");
			bossHUD->Transform()->SetRelativeScale(1127.f, 13.f, 1.f);

			qCameraMoveScript* CameraScript = Camera->GetScript<qCameraMoveScript>();
			CameraScript->SetClap(true);

			Boss->FSM()->ChangeState(L"BossIntro");

			GetOwner()->Destroy();
		}
	}

	


}

void qClapScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qClapScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qClapScript::SaveToFile(FILE* _File)
{
}

void qClapScript::LoadFromFile(FILE* _File)
{
}
