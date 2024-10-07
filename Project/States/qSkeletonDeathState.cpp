#include "pch.h"
#include "qSkeletonDeathState.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include <Scripts/qSkeletonScript.h>
#include <Scripts/qDeathSoulScript.h>
#include <States/qDeathSoulState.h>

qSkeletonDeathState::qSkeletonDeathState()
	: qState((UINT)STATE_TYPE::SKELETONDEATHSTATE)
	, Destroyflag(false)
	, Soulflag(false)
{
}

qSkeletonDeathState::~qSkeletonDeathState()
{
}

void qSkeletonDeathState::Enter()
{
	OGPos = GetOwner()->Transform()->GetRelativePos();
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	//GetOwner()->Transform()->SetRelativePos(OGPos.x - 9.f, OGPos.y + 20.f, 10.f);
	GetOwner()->Transform()->SetRelativeScale(260.f, 200.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.01f, 0.01f, 0.f));

	GetOwner()->FlipBookComponent()->Play(2, 15, false);

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Hitbox = pCurLevel->FindObjectByName(L"SkeletonAttackHitbox");

	if (Hitbox != nullptr)
	{
		Hitbox->Destroy();
		Hitbox = nullptr;
	}

	Destroyflag = false;
	Soulflag = false;
	soundflag = false;
}

void qSkeletonDeathState::FinalTick()
{
	if (!soundflag)
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\monster\\skeleton\\death.wav", L"sound\\monster\\skeleton\\death.wav");
		pSound->Play(1, 0.5, true);

		soundflag = true;
	}



	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	Ptr<qMaterial> pAlphaBlendMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DAlphaBlendMtrl");



	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished() && !Destroyflag)
	{
		GetOwner()->Destroy();

		Destroyflag = true;

	}


	// Death Soul »ý¼º

	if (!Soulflag)
	{
		qGameObject* DeathSoul = new qGameObject;
		DeathSoul->SetName(L"deathsoul");
		DeathSoul->AddComponent(new qDeathSoulScript);
		DeathSoul->AddComponent(new qTransform);
		Vec3 MonsterPos = GetOwner()->Transform()->GetRelativePos();
		Vec3 MonsterScale = GetOwner()->Transform()->GetRelativeScale();

		DeathSoul->Transform()->SetRelativePos(Vec3(MonsterPos.x, MonsterPos.y + 300.f/*(MonsterScale.y * 0.5f)*/, 30.f));
		DeathSoul->Transform()->SetRelativeScale(800.f, 800.f, 1.f);

		DeathSoul->AddComponent(new qMeshRender);
		DeathSoul->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
		DeathSoul->MeshRender()->SetMaterial(pAlphaBlendMtrl);

		DeathSoul->AddComponent(new qFlipBookComponent);
		Ptr<qFlipBook> pDeathSoul = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\deathsoul.flip");
		DeathSoul->FlipBookComponent()->AddFlipBook(0, pDeathSoul);

		DeathSoul->AddComponent(new qFSM);
		DeathSoul->FSM()->AddState(L"DeathSoul", new qDeathSoulState);

		DeathSoul->FSM()->ChangeState(L"DeathSoul");

		qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
		pCurLevel->AddObject(12, DeathSoul);


		Soulflag = true;
	}
	



}

void qSkeletonDeathState::Exit()
{
	soundflag = false;

	//GetOwner()->Transform()->SetRelativePos(OGPos);
	//GetOwner()->Transform()->SetRelativeScale(OGScale);
}
