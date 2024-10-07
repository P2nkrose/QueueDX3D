#include "pch.h"
#include "qBossRunState.h"

#include <Scripts/qBossScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qBossRunState::qBossRunState()
	: qState((UINT)STATE_TYPE::BOSSRUNSTATE)
	, m_Speed(150.f)
{
}

qBossRunState::~qBossRunState()
{
}

void qBossRunState::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(560.f, 335.f, 10.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.44f, 0.8f, 1.f));
	GetOwner()->Collider2D()->SetOffset(Vec3(0.1f, -0.05f, 0.f));

	GetOwner()->FlipBookComponent()->Play(2, 8, true);
}

void qBossRunState::FinalTick()
{
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Player = pCurLevel->FindObjectByName(L"Player");
	
	DIRECTION m_Dir = GetOwner()->GetScript<qBossScript>()->GetBossDir();
	Vec3 BossPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();
	
	if (m_Dir == DIRECTION::LEFT)
	{
		BossPos.x -= DT * m_Speed;
	}
	else if (m_Dir == DIRECTION::RIGHT)
	{
		BossPos.x += DT * m_Speed;
	}
	
	GetOwner()->Transform()->SetRelativePos(BossPos);
	
	Vec3 Dir = PlayerPos - BossPos;
	
	// 다른 방향에 있을 경우
	if (Dir.x * (int)m_Dir < 0)
	{
		ChangeState(L"BossIdle");
	}
	
	float Dist = Dir.Length();
	
	if (Dist < 700.f)
	{
		ChangeState(L"BossIdle");
	}


}

void qBossRunState::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
