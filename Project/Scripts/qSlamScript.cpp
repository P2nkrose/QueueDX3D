#include "pch.h"
#include "qSlamScript.h"

#include <Engine/qState.h>
#include <States/qStateMgr.h>

#include "qPlayerScript.h"

qSlamScript::qSlamScript()
	: qScript((UINT)SCRIPT_TYPE::SLAMSCRIPT)
	, m_SlamDamage(10.f)
{
}

qSlamScript::~qSlamScript()
{
}

void qSlamScript::Begin()
{
}

void qSlamScript::Tick()
{
}

void qSlamScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
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
				PlayerScript->Hit(m_SlamDamage);

				_OtherObject->FSM()->ChangeState(L"Bump");
			}

		}
	}
}

void qSlamScript::SaveToFile(FILE* _File)
{
}

void qSlamScript::LoadFromFile(FILE* _File)
{
}
