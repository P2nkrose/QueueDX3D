#include "pch.h"
#include "qWallScript.h"

#include <Engine/qCollider2D.h>
#include <Engine/qCollisionMgr.h>
#include <Engine/qRigidBody.h>
#include <Engine/qGameObject.h>
#include "qPlayerScript.h"
#include <Engine/qScript.h>

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qWallScript::qWallScript()
	: qScript((UINT)SCRIPT_TYPE::WALLSCRIPT)
{
}

qWallScript::~qWallScript()
{
}

void qWallScript::Begin()
{
}

void qWallScript::Tick()
{
}

void qWallScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Player")
	{
		qRigidBody* pRB = _OtherObject->GetComponent(COMPONENT_TYPE::RIGIDBODY)->RigidBody();

		pRB->SetWall(true);
	}
}

void qWallScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qWallScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Player")
	{
		qRigidBody* pRB = _OtherObject->GetComponent(COMPONENT_TYPE::RIGIDBODY)->RigidBody();

		pRB->SetWall(false);
	}
}

void qWallScript::SaveToFile(FILE* _File)
{
}

void qWallScript::LoadFromFile(FILE* _File)
{
}
