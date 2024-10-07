#include "pch.h"
#include "qBossBleedWaveState.h"

#include <Scripts/qBossScript.h>


qBossBleedWaveState::qBossBleedWaveState()
	: qState((UINT)STATE_TYPE::BOSSBLEEDWAVESTATE)
{
}

qBossBleedWaveState::~qBossBleedWaveState()
{
}

void qBossBleedWaveState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(0, 10, true);
}

void qBossBleedWaveState::FinalTick()
{

	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 1)
	{
		GetOwner()->Collider2D()->SetScale(Vec3(0.2f, 0.3f, 1.f));
		GetOwner()->Collider2D()->SetOffset(Vec3(-0.3f, -0.3f, 0.f));
	}
	else if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 2)
	{
		GetOwner()->Collider2D()->SetScale(Vec3(0.25f, 0.58f, 1.f));
		GetOwner()->Collider2D()->SetOffset(Vec3(-0.2f, -0.165f, 0.f));
	}
	else if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 3)
	{
		GetOwner()->Collider2D()->SetScale(Vec3(0.25f, 0.8f, 1.f));
		GetOwner()->Collider2D()->SetOffset(Vec3(-0.1f, -0.055f, 0.f));
	}
	else if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 5)
	{
		GetOwner()->Collider2D()->SetScale(Vec3(0.25f, 0.7f, 1.f));
		GetOwner()->Collider2D()->SetOffset(Vec3(-0.04f, -0.105f, 0.f));
	}
	else if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 6)
	{
		GetOwner()->Collider2D()->SetScale(Vec3(0.3f, 0.7f, 1.f));
		GetOwner()->Collider2D()->SetOffset(Vec3(-0.01f, -0.105f, 0.f));
	}
	else if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 7)
	{
		GetOwner()->Collider2D()->SetScale(Vec3(0.25f, 0.6f, 1.f));
		GetOwner()->Collider2D()->SetOffset(Vec3(0.15f, -0.155f, 0.f));
	}
	else if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 8)
	{
		GetOwner()->Collider2D()->SetScale(Vec3(0.2f, 0.4f, 1.f));
		GetOwner()->Collider2D()->SetOffset(Vec3(0.3f, -0.255f, 0.f));
	}


	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		if (GetOwner() != nullptr)
		{
			GetOwner()->Destroy();
		}
	
	}
}

void qBossBleedWaveState::Exit()
{
}
