#include "pch.h"
#include "qPlayerHitboxScript.h"

#include <States/qStateMgr.h>
#include "qPlayerScript.h"
#include "qSkeletonScript.h"


qPlayerHitboxScript::qPlayerHitboxScript()
	: qScript((UINT)SCRIPT_TYPE::PLAYERHITBOXSCRIPT)
	, m_Acc(0.f)
	, m_Active(false)
	, m_Duration(0.f)
	, m_Damage(0.f)
	, m_StartTime(0.f)
	, m_IsColliderActive(false)

{
}

qPlayerHitboxScript::qPlayerHitboxScript(const qPlayerHitboxScript& _Origin)
	: qScript((UINT)SCRIPT_TYPE::PLAYERHITBOXSCRIPT)
	, m_Acc(_Origin.m_Acc)
	, m_Active(_Origin.m_Active)
	, m_Duration(_Origin.m_Duration)
	, m_Damage(_Origin.m_Damage)
	, m_StartTime(_Origin.m_StartTime)
	, m_IsColliderActive(_Origin.m_IsColliderActive)
{
}

qPlayerHitboxScript::~qPlayerHitboxScript()
{
}


void qPlayerHitboxScript::On()
{
	m_Active = true;

	qGameObject* Player = GetOwner()->GetParent();
	DIRECTION Dir = Player->GetScript<qPlayerScript>()->GetPlayerDir();

	wstring CurStateName = qStateMgr::GetStateName(GetOwner()->GetParent()->FSM()->GetCurState());
	qCollider2D* Hitbox = GetOwner()->Collider2D();


	// On 된 순간 Player의 정보를 가져와 자신의 Offset, Scale 세팅
	if (CurStateName == L"qPlayerCombo1State")
	{
		Hitbox->SetOffset(Vec3(160.f, 0.f, 0.f));
		Hitbox->SetScale(Vec3(220.f, 100.f, 1.f));

		m_Damage = 10.f;

		m_StartTime = 0.0f;
		m_Duration = 0.8f;
	}
	if (CurStateName == L"qPlayerCombo2State")
	{
		Hitbox->SetOffset(Vec3(60.f, 50.f, 0.f));
		Hitbox->SetScale(Vec3(170.f, 230.f, 1.f));

		m_Damage = 10.f;

		m_StartTime = 0.f;
		m_Duration = 0.8f;
	}
	if (CurStateName == L"qPlayerCombo3State")
	{
		Hitbox->SetOffset(Vec3(100.f, 15.f, 0.f));
		Hitbox->SetScale(Vec3(320.f, 90.f, 1.f));

		m_Damage = 10.f;

		m_StartTime = 0.f;
		m_Duration = 0.8f;
	}
	if (CurStateName == L"qPlayerCombo4State")
	{
		Hitbox->SetOffset(Vec3(180.f, 50.f, 0.f));
		Hitbox->SetScale(Vec3(230.f, 230.f, 1.f));

		m_Damage = 20.f;

		m_StartTime = 0.3f;
		m_Duration = 0.8f;
	}
	if (CurStateName == L"qPlayerCrashState")
	{
		Hitbox->SetOffset(Vec3(155.f, 0.f, 0.f));
		Hitbox->SetScale(Vec3(190.f, 100.f, 1.f));

		m_Damage = 30.f;

		m_StartTime = 0.f;
		m_Duration = 0.7f;
	}
	if (CurStateName == L"qPlayerRangeState")
	{
		Hitbox->SetOffset(Vec3(0.f, 60.f, 0.f));
		Hitbox->SetScale(Vec3(230.f, 260.f, 1.f));

		m_Damage = 50.f;

		m_StartTime = 0.f;
		m_Duration = 3.f;
	}

	if (CurStateName == L"qPlayerKrushState")
	{
		Hitbox->SetOffset(Vec3(0.f, 0.f, 0.f));
		Hitbox->SetScale(Vec3(200.f, 200.f, 1.f));

		m_Damage = 30.f;

		m_StartTime = 0.3f;
		m_Duration = 0.1f;
	}



	//// 방향이 반대인 경우 뒤집어 주기
	//if (Dir == DIRECTION::RIGHT)
	//{
	//	Vec3 Offset = Hitbox->GetOffset();
	//	Offset.x *= -1;

	//	Hitbox->SetOffset(Offset);
	//}

}

void qPlayerHitboxScript::Off()
{
	GetOwner()->Collider2D()->Deactivate();
	m_Active = false;

	m_Acc = 0.f;
	m_Duration = 0.f;
	m_StartTime = 0.f;
	m_Damage = 0.f;

	m_IsColliderActive = false;
}

void qPlayerHitboxScript::Activate()
{
	// Collider 활성화
	GetOwner()->Collider2D()->Activate();
	m_IsColliderActive = true;
}


void qPlayerHitboxScript::Begin()
{
	GetOwner()->Collider2D()->Deactivate();
	GetOwner()->Collider2D()->SetIndependentScale(true);

	Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));
	Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
	Transform()->SetIndependentScale(true);

	m_Active = false;
}

void qPlayerHitboxScript::Tick()
{
	// Hitbox 가 활성화 중이 아니라면 return
	if (!m_Active)
		return;

	m_Acc += DT;

	// StartTime 이 지났고, Collider가 Active 상태가 아니라면 켜준다.
	if (m_Acc >= m_StartTime && m_IsColliderActive == false)
	{
		Activate();
	}

	if (m_Acc - m_StartTime >= m_Duration)
	{
		Off();
	}
}






void qPlayerHitboxScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	// Monster 가 아니라면 return
	qSkeletonScript* qSkeleton = _OtherObject->GetScript<qSkeletonScript>();

	if (qSkeleton == nullptr)
		return;

	qSkeleton->Hit(m_Damage);
}

void qPlayerHitboxScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qPlayerHitboxScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qPlayerHitboxScript::SaveToFile(FILE* _File)
{
}

void qPlayerHitboxScript::LoadFromFile(FILE* _File)
{
}
