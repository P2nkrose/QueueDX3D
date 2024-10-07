#include "pch.h"
#include "qGhostScript.h"

#include "qScriptMgr.h"
#include "qPlayerScript.h"
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>
#include <Engine/qRigidBody.h>
#include <Engine/qScript.h>
#include <Engine/qState.h>
#include <States/qStateMgr.h>

qGhostScript::qGhostScript()
	: qScript((UINT)SCRIPT_TYPE::GHOSTSCRIPT)
	, m_DirChanged(false)
	, m_GhostDir(DIRECTION::END)
	, m_BangTime(0.f)
	, Deathflag(false)
	, m_GhostCollisionDamage(5.f)
{
}

qGhostScript::~qGhostScript()
{
}

void qGhostScript::Begin()
{
	m_PrevUnitInfo = m_CurUnitInfo;

	m_CurUnitInfo.HP = 100.f;
	m_CurUnitInfo.Dir = DIRECTION::LEFT;

	Deathflag = false;
}

void qGhostScript::Tick()
{
	m_PrevUnitInfo = m_CurUnitInfo;

	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRotation();

	if (GetGhostDir() == DIRECTION::LEFT)
		vRot.y = 3.141592f;
	else if (GetGhostDir() == DIRECTION::RIGHT)
		vRot.y = 0.f;

	Transform()->SetRelativeRotation(vRot);


	// HP 세팅
	float CurDamage = m_PrevUnitInfo.HP - m_CurUnitInfo.HP;


	if (m_CurUnitInfo.HP <= 0 && !Deathflag)
	{
		GetOwner()->FSM()->ChangeState(L"GhostDeath");

		Deathflag = true;
	}

	// Bang 세팅
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* GhostBang = pCurLevel->FindObjectByName(L"GhostBang");

	if (GhostBang != nullptr)
	{
		GhostBang->Transform()->SetRelativePos(vPos.x, vPos.y + 150.f, 5.f);
		m_BangTime += DT;
	}

	if (GhostBang != nullptr && m_BangTime > 1.f)
	{
		GhostBang->Destroy();
		GhostBang = nullptr;
		m_BangTime = 0.f;
	}





	// Anim 방향 정보 갱신 -1: Left , 1: Right
	GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, (int)m_CurUnitInfo.Dir);
}

void qGhostScript::Hit(float _Damage)
{
	const wstring& CurState = qStateMgr::GetStateName(GetOwner()->FSM()->GetCurState());

	if (CurState == L"qGhostDeathState")
		return;

	m_CurUnitInfo.HP -= _Damage;

	GetOwner()->FSM()->ChangeState(L"GhostHit");
}


void qGhostScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
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
			PlayerScript->Hit(m_GhostCollisionDamage);

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
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\monster\\ghost\\hit.wav", L"sound\\monster\\ghost\\hit.wav");
		pSound->Play(1, 0.7, true);
	}

}

void qGhostScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qGhostScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qGhostScript::SaveToFile(FILE* _File)
{
}

void qGhostScript::LoadFromFile(FILE* _File)
{
}


