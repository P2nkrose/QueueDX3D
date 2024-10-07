#include "pch.h"
#include "qSkeletonAttackScript.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>
#include <Engine/qState.h>
#include <States/qStateMgr.h>

#include "qPlayerScript.h"

qSkeletonAttackScript::qSkeletonAttackScript()
	: qScript((UINT)SCRIPT_TYPE::SKELETONATTACKSCRIPT)
	, m_SkeletonAttackDamage(5.f)
{
}

qSkeletonAttackScript::~qSkeletonAttackScript()
{
}

void qSkeletonAttackScript::Begin()
{

}

void qSkeletonAttackScript::Tick()
{
}

void qSkeletonAttackScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	if (GetOwner() != nullptr)
	{
		if (_OtherObject->GetName() == L"Player")
		{
			qPlayerScript* PlayerScript = _OtherObject->GetScript<qPlayerScript>();

			if (PlayerScript == nullptr)
				return;

			wstring CurStateName = qStateMgr::GetStateName(_OtherObject->FSM()->GetCurState());
			if (CurStateName == L"qPlayerDashState")
			{

			}
			else
			{
				// 플레이어 피깎기
				PlayerScript->Hit(m_SkeletonAttackDamage);

				_OtherObject->FSM()->ChangeState(L"Bump");
			}


			

			
		}
	}
}

void qSkeletonAttackScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qSkeletonAttackScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qSkeletonAttackScript::SaveToFile(FILE* _File)
{
}

void qSkeletonAttackScript::LoadFromFile(FILE* _File)
{
}
