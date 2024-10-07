#include "pch.h"
#include "qSkeletonScript.h"

#include "qPlayerScript.h"
#include "qPlatformScript.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>
#include <Engine/qRigidBody.h>
#include <Engine/qScript.h>
#include <Engine/qState.h>
#include <States/qStateMgr.h>

qSkeletonScript::qSkeletonScript()
	: qScript((UINT)SCRIPT_TYPE::SKELETONSCRIPT)
	, m_DirChanged(false)
	, m_SkeletonDir(DIRECTION::LEFT)
	, m_BangTime(0.f)
	, Deathflag(false)
	, m_SkeletonCollisionDamage(5.f)
{
}

qSkeletonScript::~qSkeletonScript()
{
}

void qSkeletonScript::Begin()
{
	m_PrevUnitInfo = m_CurUnitInfo;

	m_CurUnitInfo.HP = 50.f;
	SetSkeletonDir(DIRECTION::LEFT);

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	if (pCurLevel->GetName() == L"stage2")
	{
		// idle
	}

	Deathflag = false;
}

void qSkeletonScript::Tick()
{
	m_PrevUnitInfo = m_CurUnitInfo;

	// 방향 세팅
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRotation();

	if (m_CurUnitInfo.Dir == DIRECTION::LEFT)
		vRot.y = 0.f;
	else if (m_CurUnitInfo.Dir == DIRECTION::RIGHT)
		vRot.y = 3.141592f;

	// HP 세팅
	float CurDamage = m_PrevUnitInfo.HP - m_CurUnitInfo.HP;


	if (m_CurUnitInfo.HP <= 0 && !Deathflag)
	{
		GetOwner()->FSM()->ChangeState(L"SkeletonDeath");

		Deathflag = true;
	}

	// Bang 세팅
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* SkeletonBang = pCurLevel->FindObjectByName(L"SkeletonBang");

	if (SkeletonBang != nullptr)
	{
		SkeletonBang->Transform()->SetRelativePos(vPos.x, vPos.y + 150.f, 5.f);
		m_BangTime += DT;
	}

	if (SkeletonBang != nullptr && m_BangTime > 1.0f)
	{
		SkeletonBang->Destroy();
		SkeletonBang = nullptr;
		m_BangTime = 0.f;
	}



	// Anim 방향 정보 갱신 -1: Left , 1: Right
	GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, (int)m_CurUnitInfo.Dir);
}

void qSkeletonScript::Hit(float _Damage)
{
	const wstring& CurState = qStateMgr::GetStateName(GetOwner()->FSM()->GetCurState());

	if (CurState == L"qSkeletonDeathState")
		return;

	m_CurUnitInfo.HP -= _Damage;
}

void qSkeletonScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Player")
	{
		qPlayerScript* PlayerScript = _OtherObject->GetScript<qPlayerScript>();

		if (PlayerScript == nullptr)
			return;

		wstring CurStateName = qStateMgr::GetStateName(_OtherObject->FSM()->GetCurState());
		if (CurStateName == L"qPlayerDashState")
		{

		}
		else
		{
			// 플레이어 피깎기
			PlayerScript->Hit(m_SkeletonCollisionDamage);

			_OtherObject->FSM()->ChangeState(L"Bump");
		}
	}

	if (_OtherObject->GetName() == L"Combo1HitBox" ||
		_OtherObject->GetName() == L"Combo2HitBox" ||
		_OtherObject->GetName() == L"Combo3HitBox" ||
		_OtherObject->GetName() == L"Combo4HitBox" ||
		_OtherObject->GetName() == L"Book" ||
		_OtherObject->GetName() == L"CrashHitBox" ||
		_OtherObject->GetName() == L"RangeHitBox")
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\monster\\skeleton\\hit.wav", L"sound\\monster\\skeleton\\hit.wav");
		pSound->Play(1, 0.5, true);
	}
}

void qSkeletonScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qSkeletonScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qSkeletonScript::SaveToFile(FILE* _File)
{
}

void qSkeletonScript::LoadFromFile(FILE* _File)
{
}


