#include "pch.h"
#include "qPlayerKrushState.h"

#include <Engine/qFlipBookComponent.h>
#include <Engine/qGameObject.h>
#include <Scripts/qScriptMgr.h>
#include <Scripts/qPlayerScript.h>
#include <Scripts/qPlayerHitboxScript.h>
#include <Scripts/qPlatformScript.h>
#include <Scripts/qKrushScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qPlayerKrushState::qPlayerKrushState()
	: qState((UINT)STATE_TYPE::PLAYERKRUSHSTATE)
	, m_KrushSpeed(1200.f)
	, KrushHitBox(nullptr)
{
}

qPlayerKrushState::~qPlayerKrushState()
{
}

void qPlayerKrushState::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(700.f, 700.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.19f, 0.19f, 0.f));

	GetOwner()->FlipBookComponent()->Play(21, 15, false);

	//qPlayerHitboxScript* HitboxScript = GetOwner()->GetChild(L"PlayerHitbox")->GetScript<qPlayerHitboxScript>();
	//if (HitboxScript != nullptr)
	//{
	//	HitboxScript->On();
	//}

	soundflag = false;

}

void qPlayerKrushState::FinalTick()
{
	if (!soundflag)
	{
		Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\player\\krush.wav", L"sound\\player\\krush.wav");
		pSound->Play(1, 0.5, true);

		soundflag = true;
	}


	qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
			
	if (pCurLevel->GetName() == L"stage1")
	{
		Vec3 PlayerPos = GetOwner()->Transform()->GetRelativePos();
		
		if (PlayerPos.y <= -420.f)
		{
			PlayerPos.y = -420.f;
			GetOwner()->RigidBody()->SetGround(true);
		}
		else
		{
			PlayerPos += Vec3(0.f, -1.2f, 0.f) * m_KrushSpeed * DT;
		}
		
		GetOwner()->Transform()->SetRelativePos(PlayerPos);

		
	}

	if (pCurLevel->GetName() == L"stage2")
	{
		qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();
		Vec3 PlayerPos = GetOwner()->Transform()->GetRelativePos();
		Vec3 PlayerScale = GetOwner()->Transform()->GetRelativeScale();
		
		Vec3 PlatformPos = pPlayerScript->GetCurrentPlatformPos();
		
		if (PlayerPos.y - 70.f <= PlatformPos.y + 7.5f)
		{
			PlayerPos.y = PlatformPos.y + 70.f;
			GetOwner()->RigidBody()->SetGround(true);
		}
		else
		{
			PlayerPos += Vec3(0.f, -1.2f, 0.f) * m_KrushSpeed * DT;
		}

		GetOwner()->Transform()->SetRelativePos(PlayerPos);




		//qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();
		//
		//// 현재 레벨을 가져오기
		//qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
		//
		//// 플레이어의 현재 위치를 가져오기
		//Vec3 PlayerPos = GetOwner()->Transform()->GetRelativePos();
		//
		//// 플랫폼과 닿았는지 확인
		//if (pPlayerScript->RigidBody()->IsGround())
		//{
		//	// 플레이어가 현재 닿은 플랫폼의 위치를 가져오기
		//	Vec3 PlatformPos = pPlayerScript->GetCurrentPlatformPos();
		//
		//	// 플레이어의 y 값을 플랫폼의 y 위치에 맞춰 고정
		//	PlayerPos.y = PlatformPos.y + (GetOwner()->Transform()->GetRelativeScale().y * 0.5f);
		//
		//	// 플레이어의 위치를 업데이트
		//	GetOwner()->Transform()->SetRelativePos(PlayerPos);
		//
		//	// 상태 전환
		//	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
		//	{
		//		ChangeState(L"Idle");
		//	}
		//}
		//else
		//{
		//	// 땅에 닿지 않았을 때는 계속해서 y 값을 감소시킴 (Krush 하강 로직)
		//	PlayerPos += Vec3(0.f, -1.2f, 0.f) * m_KrushSpeed * DT;
		//	GetOwner()->Transform()->SetRelativePos(PlayerPos);
		//}

	}

	if (pCurLevel->GetName() == L"stageboss")
	{
		Vec3 PlayerPos = GetOwner()->Transform()->GetRelativePos();

		if (PlayerPos.y <= -273.f)
		{
			PlayerPos.y = -273.f;
			GetOwner()->RigidBody()->SetGround(true);
		}
		else
		{
			PlayerPos += Vec3(0.f, -1.2f, 0.f) * m_KrushSpeed * DT;
		}

		GetOwner()->Transform()->SetRelativePos(PlayerPos);


	}



	//static bool hitboxCreated = false; // 히트박스 생성 여부를 추적하는 플래그
	//
	//// 히트박스 생성
	//if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 4 && !hitboxCreated)
	//{
	//	// 히트박스 생성
	//	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	//	qGameObject* pPlayer = qLevelMgr::GetInst()->FindObjectByName(L"Player");
	//	qPlayerScript* pPlayerScript = pPlayer->GetScript<qPlayerScript>();
	//	Vec3 vPlayerPos = pPlayer->Transform()->GetRelativePos();
	//
	//	KrushHitBox = new qGameObject;
	//	KrushHitBox->SetName(L"KrushHitBox");
	//	KrushHitBox->AddComponent(new qKrushScript);
	//	KrushHitBox->AddComponent(new qTransform);
	//	KrushHitBox->Transform()->SetRelativeScale(150.f, 150.f, 1.f);
	//
	//	KrushHitBox->Transform()->SetRelativePos(Vec3(vPlayerPos.x, vPlayerPos.y, vPlayerPos.z));
	//
	//
	//	KrushHitBox->AddComponent(new qCollider2D);
	//	KrushHitBox->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	//
	//	pCurLevel->AddObject(4, KrushHitBox);
	//	hitboxCreated = true; // 히트박스가 생성되었음을 표시
	//}

	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		//if (KrushHitBox != nullptr)
		//{
		//	KrushHitBox->Destroy();
		//	KrushHitBox = nullptr;
		//	hitboxCreated = false;	// 다음 상태 전환 시를 위해 플래그 초기화
		//}
	
		if(pPlayerScript->RigidBody()->IsGround())
			ChangeState(L"Idle");
	}

	//if (pPlayerScript->RigidBody()->IsGround() && GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	//{
	//	ChangeState(L"Idle");
	//}

}

void qPlayerKrushState::Exit()
{
	soundflag = false;

	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
