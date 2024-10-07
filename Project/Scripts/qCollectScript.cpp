#include "pch.h"
#include "qCollectScript.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>


qCollectScript::qCollectScript()
	: qScript((UINT)SCRIPT_TYPE::COLLECTSCRIPT)
{
	m_PlayPos = Vec3(-732.f, -87.f, 30.f);
	m_OptionPos = Vec3(-732.f, -151.f, 30.f);
	m_CreditPos = Vec3(-732.f, -214.f, 30.f);
	m_ExitPos = Vec3(-732.f, -278.f, 30.f);
}

qCollectScript::~qCollectScript()
{
}

void qCollectScript::Begin()
{
}

void qCollectScript::Tick()
{
	


	if (GetOwner()->Transform()->GetRelativePos() == m_PlayPos)
	{
		if (KEY_TAP(KEY::DOWN))
		{
			GetOwner()->Transform()->SetRelativePos(m_OptionPos);
			Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\transfer\\menu.wav", L"sound\\transfer\\menu.wav");
			pSound->Play(1, 0.8, true);
		}
	}

	else if (GetOwner()->Transform()->GetRelativePos() == m_OptionPos)
	{
		if (KEY_TAP(KEY::UP))
		{
			GetOwner()->Transform()->SetRelativePos(m_PlayPos);
			Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\transfer\\menu.wav", L"sound\\transfer\\menu.wav");
			pSound->Play(1, 0.8, true);
		}
		else if (KEY_TAP(KEY::DOWN))
		{
			GetOwner()->Transform()->SetRelativePos(m_CreditPos);
			Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\transfer\\menu.wav", L"sound\\transfer\\menu.wav");
			pSound->Play(1, 0.8, true);
		}
	}

	else if (GetOwner()->Transform()->GetRelativePos() == m_CreditPos)
	{
		if (KEY_TAP(KEY::UP))
		{
			GetOwner()->Transform()->SetRelativePos(m_OptionPos);
			Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\transfer\\menu.wav", L"sound\\transfer\\menu.wav");
			pSound->Play(1, 0.8, true);
		}
		else if (KEY_TAP(KEY::DOWN))
		{
			GetOwner()->Transform()->SetRelativePos(m_ExitPos);
			Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\transfer\\menu.wav", L"sound\\transfer\\menu.wav");
			pSound->Play(1, 0.8, true);
		}
	}

	else if (GetOwner()->Transform()->GetRelativePos() == m_ExitPos)
	{
		if (KEY_TAP(KEY::UP))
		{
			GetOwner()->Transform()->SetRelativePos(m_CreditPos);
			Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\transfer\\menu.wav", L"sound\\transfer\\menu.wav");
			pSound->Play(1, 0.8, true);
		}
	}


	if (GetOwner()->Transform()->GetRelativePos() == m_PlayPos)
	{
		if (KEY_TAP(KEY::SPACE))
		{
			Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\transfer\\gameplay.wav", L"sound\\transfer\\gameplay.wav");
			pSound->Play(1, 0.7, true);

			qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
			qGameObject* pPostClose = pCurLevel->FindObjectByName(L"PostClose");

			pPostClose->FSM()->ChangeState(L"PostClose");
		}
	}


}

void qCollectScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qCollectScript::SaveToFile(FILE* _File)
{
}

void qCollectScript::LoadFromFile(FILE* _File)
{
}
