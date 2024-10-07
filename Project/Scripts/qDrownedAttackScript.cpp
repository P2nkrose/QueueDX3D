#include "pch.h"
#include "qDrownedAttackScript.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>
#include <Engine/qState.h>
#include <States/qStateMgr.h>

#include "qPlayerScript.h"

qDrownedAttackScript::qDrownedAttackScript()
	: qScript((UINT)SCRIPT_TYPE::DROWNEDATTACKSCRIPT)
	, m_DrownedAttackDamage(5.f)
{
}

qDrownedAttackScript::~qDrownedAttackScript()
{
}

void qDrownedAttackScript::Begin()
{
}

void qDrownedAttackScript::Tick()
{
}

void qDrownedAttackScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
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
				PlayerScript->Hit(m_DrownedAttackDamage);

				_OtherObject->FSM()->ChangeState(L"Bump");
			}


			

			
		}
	}
}

void qDrownedAttackScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qDrownedAttackScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qDrownedAttackScript::SaveToFile(FILE* _File)
{
}

void qDrownedAttackScript::LoadFromFile(FILE* _File)
{
}
