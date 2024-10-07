#include "pch.h"
#include "qGhostAttackScript.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include <Engine/qState.h>
#include <States/qStateMgr.h>

#include "qPlayerScript.h"
#include "qGhostScript.h"

qGhostAttackScript::qGhostAttackScript()
	: qScript((UINT)SCRIPT_TYPE::GHOSTATTACKSCRIPT)
	, m_GhostAttackDamage(5.f)
{

}

qGhostAttackScript::~qGhostAttackScript()
{
}

void qGhostAttackScript::Begin()
{

}

void qGhostAttackScript::Tick()
{

}

void qGhostAttackScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
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
				PlayerScript->Hit(m_GhostAttackDamage);

				_OtherObject->FSM()->ChangeState(L"Bump");
			}


			

			
		}
	}
}

void qGhostAttackScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qGhostAttackScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qGhostAttackScript::SaveToFile(FILE* _File)
{
}

void qGhostAttackScript::LoadFromFile(FILE* _File)
{
}
