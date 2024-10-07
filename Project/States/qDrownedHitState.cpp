#include "pch.h"
#include "qDrownedHitState.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include <Scripts/qDrownedScript.h>

qDrownedHitState::qDrownedHitState()
	: qState((UINT)STATE_TYPE::DROWNEDHITSTATE)
	, m_DrownedBumpSpeed(200.f)
	, m_MaxRange(0.f)
{
}

qDrownedHitState::~qDrownedHitState()
{
}

void qDrownedHitState::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(300.f, 260.f, 10.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.5f, 0.88f, 1.f));

	GetOwner()->FlipBookComponent()->Play(4, 8, false);

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Hitbox = pCurLevel->FindObjectByName(L"DrownedAttackHitbox");

	if (Hitbox != nullptr)
		Hitbox->Destroy();
}

void qDrownedHitState::FinalTick()
{
	qDrownedScript* DrownedScript = GetOwner()->GetScript<qDrownedScript>();
	Vec3 DrownedPos = GetOwner()->Transform()->GetRelativePos();

	if (DrownedScript->GetDrownedDir() == DIRECTION::LEFT)
	{
		m_MaxRange += m_DrownedBumpSpeed * DT;
		DrownedPos += Vec3(0.5f, 0.f, 0.f) * m_DrownedBumpSpeed * DT;
	}
	else if (DrownedScript->GetDrownedDir() == DIRECTION::RIGHT)
	{
		m_MaxRange += m_DrownedBumpSpeed * DT;
		DrownedPos += Vec3(-0.5f, 0.f, 0.f) * m_DrownedBumpSpeed * DT;
	}

	if (50.f < m_MaxRange)
	{
		m_MaxRange = 0.f;
	}

	GetOwner()->Transform()->SetRelativePos(DrownedPos);


	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"DrownedIdle");
	}
}

void qDrownedHitState::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
