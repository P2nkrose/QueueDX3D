#include "pch.h"
#include "qRangeScript.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include "qPlayerScript.h"
#include "qSkeletonScript.h"
#include "qDrownedScript.h"
#include "qGhostScript.h"
#include "qBossScript.h"
#include "qPlayerEffectScript.h"
#include <States/qPlayerEffectState.h>

qRangeScript::qRangeScript()
	: qScript((UINT)SCRIPT_TYPE::RANGESCRIPT)
	, m_RangeDamage(50.f)
{
}

qRangeScript::~qRangeScript()
{
}

void qRangeScript::Begin()
{
}

void qRangeScript::Tick()
{
}

void qRangeScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Player = pCurLevel->FindObjectByName(L"Player");
	qPlayerScript* PlayerScript = Player->GetScript<qPlayerScript>();
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();
	Vec3 RangePos = GetOwner()->Transform()->GetRelativePos();
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	Ptr<qMaterial> pAlphaBlendMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DAlphaBlendMtrl");


	if (GetOwner() != nullptr)
	{
		if (_OtherObject->GetName() == L"Skeleton")
		{
			qSkeletonScript* SkeletonScript = _OtherObject->GetScript<qSkeletonScript>();

			if (SkeletonScript == nullptr)
				return;

			SkeletonScript->Hit(m_RangeDamage);
		}
		else if (_OtherObject->GetName() == L"Drowned")
		{
			qDrownedScript* DrownedScript = _OtherObject->GetScript<qDrownedScript>();

			if (DrownedScript == nullptr)
				return;

			DrownedScript->Hit(m_RangeDamage);
		}
		else if (_OtherObject->GetName() == L"Ghost")
		{
			qGhostScript* GhostScript = _OtherObject->GetScript<qGhostScript>();

			if (GhostScript == nullptr)
				return;

			GhostScript->Hit(m_RangeDamage);
		}
		else if (_OtherObject->GetName() == L"Boss")
		{
			qBossScript* BossScript = _OtherObject->GetScript<qBossScript>();

			if (BossScript == nullptr)
				return;

			BossScript->Hit(m_RangeDamage);
		}


		// ÀÌÆåÆ®
		if (_OtherObject->GetName() == L"Skeleton" ||
			_OtherObject->GetName() == L"Drowned" ||
			_OtherObject->GetName() == L"Ghost" ||
			_OtherObject->GetName() == L"Boss")
		{
			qGameObject* Effect = new qGameObject;
			Effect->SetName(L"effect");
			Effect->AddComponent(new qPlayerEffectScript);
			Effect->AddComponent(new qTransform);
			Vec3 MonsterPos = _OtherObject->Transform()->GetRelativePos();
			Vec3 MonsterScale = _OtherObject->Transform()->GetRelativeScale();

			if (_OtherObject->GetName() == L"Skeleton")
			{
				qSkeletonScript* SkeletonScript = _OtherObject->GetScript<qSkeletonScript>();
				if (SkeletonScript->GetSkeletonDir() == DIRECTION::LEFT)
					Effect->Transform()->SetRelativePos(Vec3(MonsterPos.x - (MonsterScale.x * 0.5f), MonsterPos.y, MonsterPos.z));
				else if (SkeletonScript->GetSkeletonDir() == DIRECTION::RIGHT)
					Effect->Transform()->SetRelativePos(Vec3(MonsterPos.x + (MonsterScale.x * 0.5f), MonsterPos.y, MonsterPos.z));
			}
			else if (_OtherObject->GetName() == L"Drowned")
			{
				if (PlayerScript->GetPlayerDir() == DIRECTION::LEFT)
					Effect->Transform()->SetRelativePos(Vec3(MonsterPos.x + 30.f, MonsterPos.y - 30.f, 10.f));
				else if (PlayerScript->GetPlayerDir() == DIRECTION::RIGHT)
					Effect->Transform()->SetRelativePos(Vec3(MonsterPos.x - 30.f, MonsterPos.y - 30.f, 10.f));
			}
			else if (_OtherObject->GetName() == L"Ghost")
			{
				if (PlayerScript->GetPlayerDir() == DIRECTION::LEFT)
					Effect->Transform()->SetRelativePos(Vec3(MonsterPos.x + 30.f, MonsterPos.y - 30.f, 10.f));
				else if (PlayerScript->GetPlayerDir() == DIRECTION::RIGHT)
					Effect->Transform()->SetRelativePos(Vec3(MonsterPos.x - 30.f, MonsterPos.y - 30.f, 10.f));
			}
			else if (_OtherObject->GetName() == L"Boss")
			{
				if (PlayerScript->GetPlayerDir() == DIRECTION::LEFT)
					Effect->Transform()->SetRelativePos(Vec3(MonsterPos.x + 180.f, MonsterPos.y - 100.f, 1.f));
				else if (PlayerScript->GetPlayerDir() == DIRECTION::RIGHT)
					Effect->Transform()->SetRelativePos(Vec3(MonsterPos.x - 180.f, MonsterPos.y - 100.f, 1.f));
			}

			Effect->Transform()->SetRelativeScale(180.f, 180.f, 1.f);

			Effect->AddComponent(new qMeshRender);
			Effect->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
			Effect->MeshRender()->SetMaterial(pAlphaBlendMtrl);

			Effect->AddComponent(new qFlipBookComponent);
			Ptr<qFlipBook> pEffect = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\effect.flip");
			Effect->FlipBookComponent()->AddFlipBook(0, pEffect);

			Effect->AddComponent(new qFSM);
			Effect->FSM()->AddState(L"Effect", new qPlayerEffectState);

			Effect->FSM()->ChangeState(L"Effect");

			qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
			pCurLevel->AddObject(12, Effect);
		}


	}

}

void qRangeScript::SaveToFile(FILE* _File)
{
}

void qRangeScript::LoadFromFile(FILE* _File)
{
}
