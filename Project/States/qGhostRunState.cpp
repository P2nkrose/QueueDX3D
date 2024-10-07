#include "pch.h"
#include "qGhostRunState.h"

#include <Scripts/qGhostScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qGhostRunState::qGhostRunState()
	: qState((UINT)STATE_TYPE::GHOSTRUNSTATE)
	, m_Speed(300.f)
{
}

qGhostRunState::~qGhostRunState()
{
}

void qGhostRunState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(1, 10, true);
}

void qGhostRunState::FinalTick()
{
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Player = pCurLevel->FindObjectByName(L"Player");

	DIRECTION m_Dir = GetOwner()->GetScript<qGhostScript>()->GetGhostDir();
	Vec3 GhostPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();

	if (m_Dir == DIRECTION::LEFT)
	{
		GhostPos.x -= DT * m_Speed;
	}
	else if (m_Dir == DIRECTION::RIGHT)
	{
		GhostPos.x += DT * m_Speed;
	}

	GetOwner()->Transform()->SetRelativePos(GhostPos);

	Vec3 Dir = PlayerPos - GhostPos;

	// 다른 방향에 있을 경우
	if (Dir.x * (int)m_Dir < 0)
	{
		ChangeState(L"GhostIdle");
	}

	float Dist = Dir.Length();

	if (Dist < 200.f)
	{
		ChangeState(L"GhostIdle");
	}
}

void qGhostRunState::Exit()
{
}
