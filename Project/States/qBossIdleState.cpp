#include "pch.h"
#include "qBossIdleState.h"

#include <Scripts/qBossScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qBossIdleState::qBossIdleState()
	: qState((UINT)STATE_TYPE::BOSSIDLESTATE)
	, m_DetectRange(1200.f)
	, m_AttackRange(700.f)
	, UturnFlag(false)
{
}

qBossIdleState::~qBossIdleState()
{
}

void qBossIdleState::Enter()
{
	OGPos = GetOwner()->Transform()->GetRelativePos();
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativePos(OGPos.x, OGPos.y - 11.f, OGPos.z);
	GetOwner()->Collider2D()->SetScale(Vec3(0.5f, 0.9f, 0.f));
	GetOwner()->Collider2D()->SetOffset(Vec3(0.15f, -0.02f, 0.f));

	GetOwner()->FlipBookComponent()->Play(1, 8, true);
}

void qBossIdleState::FinalTick()
{
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Player = pCurLevel->FindObjectByName(L"Player");
	Vec3 BossPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();
	Vec3 Dir = PlayerPos - BossPos;
	float Dist = Dir.Length();

	

	if (Dist < m_DetectRange)
	{
		DIRECTION CurDir = GetOwner()->GetScript<qBossScript>()->GetBossDir();

		// 같은 방향
		if (Dir.x * (int)CurDir > 0)
		{
			ChangeState(L"BossRun");
		}
		else if(Dir.x * (int)CurDir <= 0 && !UturnFlag)
		{
			ChangeState(L"BossUturn");

			UturnFlag = true;
		}
	}

	int state = rand() % 3;

	if (Dist < m_AttackRange)
	{
		DIRECTION CurDir = GetOwner()->GetScript<qBossScript>()->GetBossDir();

		//m_Time += DT;

		// 같은 방향
		if (Dir.x * (int)CurDir > 0)
		{
			if (state == 0)
			{
				ChangeState(L"BossPunch");
			}
			else if (state == 1)
			{
				ChangeState(L"BossSlam");
			}
			else if (state == 2)
			{
				ChangeState(L"BossBleed");
			}
		}
		else if (Dir.x * (int)CurDir <= 0 && !UturnFlag)
		{
			ChangeState(L"BossUturn");

			UturnFlag = true;
		}
	}



	if (KEY_TAP(KEY::Q))
	{
		ChangeState(L"BossPunch");
	}
	else if (KEY_TAP(KEY::W))
	{
		ChangeState(L"BossSlam");
	}
	else if (KEY_TAP(KEY::E))
	{
		ChangeState(L"BossBleed");
	}


}

void qBossIdleState::Exit()
{
	GetOwner()->Transform()->SetRelativePos(OGPos);
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);

	m_Time = 0.f;

	UturnFlag = false;
}
