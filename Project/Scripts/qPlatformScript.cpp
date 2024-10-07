#include "pch.h"
#include "qPlatformScript.h"

#include <Engine/qCollider2D.h>
#include <Engine/qCollisionMgr.h>
#include <Engine/qRigidBody.h>
#include <Engine/qGameObject.h>
#include "qPlayerScript.h"
#include <Engine/qScript.h>

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>


qPlatformScript::qPlatformScript()
	: qScript(UINT(SCRIPT_TYPE::PLATFORMSCRIPT))
{
}

qPlatformScript::~qPlatformScript()
{
}

void qPlatformScript::Begin()
{
	
}

void qPlatformScript::Tick()
{

}

void qPlatformScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Player")
	{
		qRigidBody* pRB = _OtherObject->GetComponent(COMPONENT_TYPE::RIGIDBODY)->RigidBody();
		
		Vec3 PlatformPos = GetOwner()->Transform()->GetRelativePos();

		Vec3 PlayerPos = _OtherObject->Transform()->GetRelativePos();
		Vec3 PlayerScale = _OtherObject->Transform()->GetRelativeScale();

		if (PlatformPos.y <= PlayerPos.y/* - (PlayerScale.y * 0.5f)*/)
		{
			pRB->SetGround(true);
			qPlayerScript* pPlayerScript = _OtherObject->GetScript<qPlayerScript>();
			pPlayerScript->SetCurrentPlatformPos(PlatformPos);
		}
	}

	//if (_OtherObject->GetName() == L"Boss")
	//{
	//	qRigidBody* pRB = _OtherObject->GetComponent(COMPONENT_TYPE::RIGIDBODY)->RigidBody();
	//
	//	pRB->SetGround(true);
	//}

}

void qPlatformScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qPlatformScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Player")
	{
		qRigidBody* pRB = _OtherObject->GetComponent(COMPONENT_TYPE::RIGIDBODY)->RigidBody();

		pRB->SetGround(false);
	}

}

void qPlatformScript::SaveToFile(FILE* _File)
{
	
}

void qPlatformScript::LoadFromFile(FILE* _File)
{
	
}
