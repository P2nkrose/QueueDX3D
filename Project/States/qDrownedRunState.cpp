#include "pch.h"
#include "qDrownedRunState.h"

#include <Scripts/qDrownedScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qDrownedRunState::qDrownedRunState()
	: qState((UINT)STATE_TYPE::DROWNEDRUNSTATE)
	, m_Speed(300.f)
{
}

qDrownedRunState::~qDrownedRunState()
{
}

void qDrownedRunState::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();
	

	GetOwner()->Transform()->SetRelativeScale(200.f, 250.f, 10.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.75f, 0.92f, 1.f));

	GetOwner()->FlipBookComponent()->Play(1, 10, true);

}

void qDrownedRunState::FinalTick()
{
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Player = pCurLevel->FindObjectByName(L"Player");

	DIRECTION m_Dir = GetOwner()->GetScript<qDrownedScript>()->GetDrownedDir();
	Vec3 DrownedPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();

	if (m_Dir == DIRECTION::LEFT)
	{
		DrownedPos.x -= DT * m_Speed;
	}
	else if (m_Dir == DIRECTION::RIGHT)
	{
		DrownedPos.x += DT * m_Speed;
	}

	GetOwner()->Transform()->SetRelativePos(DrownedPos);

	Vec3 Dir = PlayerPos - DrownedPos;
	
	// 다른 방향에 있을 경우
	if (Dir.x * (int)m_Dir < 0)
	{
		ChangeState(L"DrownedIdle");
	}
	
	float Dist = Dir.Length();

	if (Dist < 200.f)
	{
		ChangeState(L"DrownedIdle");
	}

}

void qDrownedRunState::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
