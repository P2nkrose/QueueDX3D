#include "pch.h"
#include "qPunchScript.h"

#include <Engine/qState.h>
#include <States/qStateMgr.h>

#include "qPlayerScript.h"

qPunchScript::qPunchScript()
	: qScript((UINT)SCRIPT_TYPE::PUNCHSCRIPT)
	, m_PunchDamage(10.f)
{
}

qPunchScript::~qPunchScript()
{
}

void qPunchScript::Begin()
{
}

void qPunchScript::Tick()
{
}

void qPunchScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
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
				PlayerScript->Hit(m_PunchDamage);

				_OtherObject->FSM()->ChangeState(L"Bump");
			}


			

			
		}
	}
}

void qPunchScript::SaveToFile(FILE* _File)
{
}

void qPunchScript::LoadFromFile(FILE* _File)
{
}
