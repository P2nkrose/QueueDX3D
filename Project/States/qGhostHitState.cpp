#include "pch.h"
#include "qGhostHitState.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include <Scripts/qGhostScript.h>

qGhostHitState::qGhostHitState()
	: qState((UINT)STATE_TYPE::GHOSTHITSTATE)
	, m_GhostBumpSpeed(200.f)
	, m_MaxRange(0.f)
{
}

qGhostHitState::~qGhostHitState()
{
}

void qGhostHitState::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(250.f, 250.f, 10.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.8f, 1.f, 1.f));

	GetOwner()->FlipBookComponent()->Play(4, 15, false);

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Hitbox = pCurLevel->FindObjectByName(L"GhostAttackHitbox");

	if (Hitbox != nullptr)
		Hitbox->Destroy();
}

void qGhostHitState::FinalTick()
{
	qGhostScript* GhostScript = GetOwner()->GetScript<qGhostScript>();
	Vec3 GhostPos = GetOwner()->Transform()->GetRelativePos();

	if (GhostScript->GetGhostDir() == DIRECTION::LEFT)
	{
		m_MaxRange += m_GhostBumpSpeed * DT;
		GhostPos += Vec3(0.5f, 0.f, 0.f) * m_GhostBumpSpeed * DT;
	}
	else if (GhostScript->GetGhostDir() == DIRECTION::RIGHT)
	{
		m_MaxRange += m_GhostBumpSpeed * DT;
		GhostPos += Vec3(-0.5f, 0.f, 0.f) * m_GhostBumpSpeed * DT;
	}

	if (50.f < m_MaxRange)
	{
		m_MaxRange = 0.f;
	}

	GetOwner()->Transform()->SetRelativePos(GhostPos);

	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"GhostIdle");
	}
}

void qGhostHitState::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
