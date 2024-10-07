#include "pch.h"
#include "qBookScript_Left.h"

#include <Engine/qGameObject.h>
#include <Engine/qLevelMgr.h>
#include <Engine/qLevel.h>

#include <Engine/qScript.h>
#include "qPlayerScript.h"
#include "qSkeletonScript.h"
#include "qDrownedScript.h"
#include "qGhostScript.h"
#include "qBossScript.h"
#include "qPlayerEffectScript.h"
#include <States/qPlayerEffectState.h>
#include <States/qBookEffectState.h>


qBookScript_Left::qBookScript_Left()
	: qScript(UINT(SCRIPT_TYPE::BOOKSCRIPT_LEFT))
	, m_BookSpeed(1000.f)
	, m_BookDamage(30.f)
{
}

qBookScript_Left::~qBookScript_Left()
{
}

void qBookScript_Left::Begin()
{
	//GetOwner()->FlipBookComponent()->Play(18, 15, true);
}

void qBookScript_Left::Tick()
{
	//qGameObject* pPlayer = qLevelMgr::GetInst()->FindObjectByName(L"Player");
	//
	//qPlayerScript* pPlayerScript = pPlayer->GetScript<qPlayerScript>();

	Vec3 vPos = Transform()->GetRelativePos();

	vPos.x -= DT * m_BookSpeed;

	Transform()->SetRelativePos(vPos);
}

void qBookScript_Left::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	Ptr<qMaterial> pAlphaBlendMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DAlphaBlendMtrl");

	if (GetOwner() != nullptr)
	{
		if (_OtherObject->GetName() == L"Skeleton")
		{
			qSkeletonScript* SkeletonScript = _OtherObject->GetScript<qSkeletonScript>();

			if (SkeletonScript == nullptr)
				return;

			SkeletonScript->Hit(m_BookDamage);

			GetOwner()->Destroy();
		}
		else if (_OtherObject->GetName() == L"Drowned")
		{
			qDrownedScript* DrownedScript = _OtherObject->GetScript<qDrownedScript>();

			if (DrownedScript == nullptr)
				return;

			DrownedScript->Hit(m_BookDamage);

			GetOwner()->Destroy();
		}
		else if (_OtherObject->GetName() == L"Ghost")
		{
			qGhostScript* GhostScript = _OtherObject->GetScript<qGhostScript>();

			if (GhostScript == nullptr)
				return;

			GhostScript->Hit(m_BookDamage);

			GetOwner()->Destroy();
		}
		else if (_OtherObject->GetName() == L"Boss")
		{
			qBossScript* BossScript = _OtherObject->GetScript<qBossScript>();

			if (BossScript == nullptr)
				return;

			BossScript->Hit(m_BookDamage);

			GetOwner()->Destroy();
		}


		// ÀÌÆåÆ®
		if (_OtherObject->GetName() == L"Skeleton" ||
			_OtherObject->GetName() == L"Drowned" ||
			_OtherObject->GetName() == L"Ghost" ||
			_OtherObject->GetName() == L"Boss")
		{
			qGameObject* Effect = new qGameObject;
			Effect->SetName(L"effect");

			Effect->AddComponent(new qTransform);
			Vec3 MonsterPos = _OtherObject->Transform()->GetRelativePos();
			Vec3 MonsterScale = _OtherObject->Transform()->GetRelativeScale();
			
			if (_OtherObject->GetName() == L"Skeleton")
			{
				Effect->Transform()->SetRelativePos(Vec3(MonsterPos.x + 20.f, MonsterPos.y - 30.f, 1.f));
			}
			else if (_OtherObject->GetName() == L"Drowned" || _OtherObject->GetName() == L"Ghost")
			{
				Effect->Transform()->SetRelativePos(Vec3(MonsterPos.x + 20.f, MonsterPos.y - 30.f, 1.f));
			}
			else if (_OtherObject->GetName() == L"Boss")
			{
				Effect->Transform()->SetRelativePos(Vec3(MonsterPos.x + 180.f, MonsterPos.y - 100.f, 1.f));
			}

			Effect->Transform()->SetRelativeScale(90.f, 90.f, 1.f);

			Effect->AddComponent(new qMeshRender);
			Effect->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
			Effect->MeshRender()->SetMaterial(pMtrl);

			Effect->AddComponent(new qFlipBookComponent);
			Ptr<qFlipBook> pEffect = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\bookeffect.flip");
			Effect->FlipBookComponent()->AddFlipBook(0, pEffect);

			Effect->AddComponent(new qFSM);
			Effect->FSM()->AddState(L"Effect", new qBookEffectState);

			Effect->FSM()->ChangeState(L"Effect");

			qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
			pCurLevel->AddObject(12, Effect);
		}


	}




}

void qBookScript_Left::SaveToFile(FILE* _File)
{
	fwrite(&m_BookSpeed, sizeof(float), 1, _File);
}

void qBookScript_Left::LoadFromFile(FILE* _File)
{
	fread(&m_BookSpeed, sizeof(float), 1, _File);
}
