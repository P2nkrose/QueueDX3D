#include "pch.h"
#include "qDoorScript.h"

qDoorScript::qDoorScript()
	: qScript((UINT)SCRIPT_TYPE::DOORSCRIPT)
{
}

qDoorScript::~qDoorScript()
{
}

void qDoorScript::Begin()
{
}

void qDoorScript::Tick()
{
}

void qDoorScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{

	if (_OtherObject->GetName() == L"Player")
	{
		FSM()->ChangeState(L"DoorOpen");
	}
}

void qDoorScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{

}

void qDoorScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Player")
	{
		FSM()->ChangeState(L"DoorClose");
	}
}

void qDoorScript::SaveToFile(FILE* _File)
{
}

void qDoorScript::LoadFromFile(FILE* _File)
{
}
