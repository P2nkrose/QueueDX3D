#include "pch.h"
#include "qGhostAttackState.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include <Scripts/qGhostScript.h>
#include <Scripts/qGhostAttackScript.h>

#include "qFireState.h"

qGhostAttackState::qGhostAttackState()
	: qState((UINT)STATE_TYPE::GHOSTATTACKSTATE)
	, GhostAttackHitbox(nullptr)
{
}

qGhostAttackState::~qGhostAttackState()
{
}

void qGhostAttackState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(3, 12, false);


	// 히트박스 (애니메이션) 생성
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	Ptr<qMaterial> pAlphaBlendMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DAlphaBlendMtrl");
	
	// 이펙트
	Ptr<qMaterial> pEffectMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"EffectMtrl");

	qGhostScript* GhostScript = GetOwner()->GetScript<qGhostScript>();
	Vec3 GhostPos = GetOwner()->Transform()->GetRelativePos();

	GhostAttackHitbox = new qGameObject;
	GhostAttackHitbox->SetName(L"GhostAttackHitbox");
	GhostAttackHitbox->AddComponent(new qGhostAttackScript);
	GhostAttackHitbox->AddComponent(new qTransform);
	GhostAttackHitbox->Transform()->SetRelativeScale(275.f, 155.f, 1.f);

	if (GhostScript->GetGhostDir() == DIRECTION::LEFT)
	{
		GhostAttackHitbox->Transform()->SetRelativePos(Vec3(GhostPos.x - 200.f, GhostPos.y - 30.f, 1.f));
		GhostAttackHitbox->Transform()->SetRelativeRotation(0.f, 3.141592f, 0.f);
	}
	else if (GhostScript->GetGhostDir() == DIRECTION::RIGHT)
	{
		GhostAttackHitbox->Transform()->SetRelativePos(Vec3(GhostPos.x + 200.f, GhostPos.y - 30.f, 1.f));
	}

	GhostAttackHitbox->AddComponent(new qMeshRender);
	GhostAttackHitbox->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	GhostAttackHitbox->MeshRender()->SetMaterial(pEffectMtrl);

	GhostAttackHitbox->MeshRender()->GetMaterial()->SetScalarParam(VEC4_0, Vec4(20.f, 3.f, 3.f, 1.f));


	GhostAttackHitbox->AddComponent(new qCollider2D);
	GhostAttackHitbox->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	GhostAttackHitbox->AddComponent(new qFlipBookComponent);

	Ptr<qFlipBook> pFire = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\fire.flip");
	GhostAttackHitbox->FlipBookComponent()->AddFlipBook(0, pFire);

	GhostAttackHitbox->AddComponent(new qFSM);
	GhostAttackHitbox->FSM()->AddState(L"Fire", new qFireState);

	GhostAttackHitbox->FSM()->ChangeState(L"Fire");

}

void qGhostAttackState::FinalTick()
{
	static bool hitbox = false;

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	// Index 맞춰서 히트박스 생성
	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 16 && !hitbox)
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\monster\\ghost\\attack1.wav", L"sound\\monster\\ghost\\attack1.wav");
		pSound->Play(1, 1.0, true);

		pCurLevel->AddObject(6, GhostAttackHitbox);
		hitbox = true;
	}

	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"GhostIdle");

		if (GhostAttackHitbox != nullptr)
		{
			GhostAttackHitbox->Destroy();
			GhostAttackHitbox = nullptr;
			hitbox = false;
		}
	}
}

void qGhostAttackState::Exit()
{

}
