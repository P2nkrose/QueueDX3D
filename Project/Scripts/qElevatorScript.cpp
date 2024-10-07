#include "pch.h"
#include "qElevatorScript.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include "qCameraMoveScript.h"
#include "qPlayerScript.h"

qElevatorScript::qElevatorScript()
	: qScript((UINT)SCRIPT_TYPE::ELEVATORSCRIPT)
{
}

qElevatorScript::~qElevatorScript()
{
}

void qElevatorScript::Begin()
{

}

void qElevatorScript::Tick()
{
	//qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	//qGameObject* Player = pCurLevel->FindObjectByName(L"Player");
	//qGameObject* Camera = pCurLevel->FindObjectByName(L"MainCamera");
	//Vec3 PlayerPos = Player->Transform()->GetRelativePos();
	//Vec3 CameraPos1 = Camera->Transform()->GetRelativePos();

	//qCameraMoveScript* CameraScript = Camera->GetScript<qCameraMoveScript>();
	//qPlayerScript* PlayerScript = Player->GetScript<qPlayerScript>();

	//static bool flag = false;

	//if (PlayerPos.y >= 5000.f && !flag)
	//{
	//	FixPos = CameraPos1;

	//	flag = true;
	//}
}

void qElevatorScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qElevatorScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	//qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	//qGameObject* Player = pCurLevel->FindObjectByName(L"Player");
	//qGameObject* Camera = pCurLevel->FindObjectByName(L"MainCamera");
	//Vec3 PlayerPos = Player->Transform()->GetRelativePos();
	//Vec3 CameraPos = Camera->Transform()->GetRelativePos();

	//qCameraMoveScript* CameraScript = Camera->GetScript<qCameraMoveScript>();
	//qPlayerScript* PlayerScript = Player->GetScript<qPlayerScript>();

	//if (_OtherObject->GetName() == L"Player")
	//{
	//	Camera->Transform()->SetRelativePos(Vec3(CameraPos.x, FixPos.y + 200.f, CameraPos.z));
	//}

}

void qElevatorScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qElevatorScript::SaveToFile(FILE* _File)
{
}

void qElevatorScript::LoadFromFile(FILE* _File)
{
}
