#include "pch.h"
#include "qGhostIdleState.h"

#include <Scripts/qGhostScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qGhostIdleState::qGhostIdleState()
	: qState((UINT)STATE_TYPE::GHOSTIDLESTATE)
	, m_DetectRange(600.f)
	, m_AttackRange(200.f)
	, m_Bang(nullptr)
	, Bangflag(false)
{
}

qGhostIdleState::~qGhostIdleState()
{
}

void qGhostIdleState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(0, 10, true);
}

void qGhostIdleState::FinalTick()
{
	//Ptr<qMaterial> pBangMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"material\\bang.mtrl");
	Ptr<qMaterial> pEffectMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"EffectMtrl");

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Player = pCurLevel->FindObjectByName(L"Player");

	Vec3 GhostPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();

	Vec3 Dir = PlayerPos - GhostPos;

	float Dist = Dir.Length();

	Bangflag = false;

	if (Dist < m_DetectRange && !Bangflag)
	{
		// 느낌표 생성
		m_Bang = new qGameObject;
		m_Bang->SetName(L"GhostBang");

		m_Bang->AddComponent(new qMeshRender);
		m_Bang->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
		m_Bang->MeshRender()->SetMaterial(pEffectMtrl);
		m_Bang->MeshRender()->GetMaterial()->SetScalarParam(VEC4_0, Vec4(20.f, 3.f, 3.f, 1.f));
		m_Bang->MeshRender()->GetMaterial()->SetTexParam(TEX_0, qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\monster\\bang.png"));

		m_Bang->AddComponent(new qTransform);
		m_Bang->Transform()->SetRelativePos(GhostPos.x, GhostPos.y + 150.f, 5.f);
		m_Bang->Transform()->SetRelativeScale(25.f, 80.f, 1.f);

		pCurLevel->AddObject(12, m_Bang);


		Bangflag = true;
	}



	if (Dist < m_DetectRange)
	{
		DIRECTION CurDir = GetOwner()->GetScript<qGhostScript>()->GetGhostDir();

		// 같은 방향
		if (Dir.x * (int)CurDir > 0)
		{
			ChangeState(L"GhostRun");
		}
		else
		{
			ChangeState(L"GhostUturn");
		}
	}

	if (Dist < m_AttackRange)
	{
		DIRECTION CurDir = GetOwner()->GetScript<qGhostScript>()->GetGhostDir();

		// 같은 방향
		if (Dir.x * (int)CurDir > 0)
		{
			ChangeState(L"GhostAttack");
		}
		else
		{
			ChangeState(L"GhostUturn");
		}
	}
}

void qGhostIdleState::Exit()
{
	Bangflag = false;
}
