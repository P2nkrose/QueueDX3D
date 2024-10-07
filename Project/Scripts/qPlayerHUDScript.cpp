#include "pch.h"
#include "qPlayerHUDScript.h"

#include <Engine/qSprite.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>
#include <Engine/qDevice.h>
#include <Engine/qConstBuffer.h>
#include <Engine/qGameObject.h>

#include <Scripts/qPlayerScript.h>



qPlayerHUDScript::qPlayerHUDScript()
	: qScript((UINT)SCRIPT_TYPE::PLAYERHUDSCRIPT)
	, m_MaxPlayerHP(1.f)
	, m_CurPlayerHP(1.f)
	, m_DamageHP(0.f)
	, m_FiveCount(0)
	, m_TenCount(0)
{
}

qPlayerHUDScript::~qPlayerHUDScript()
{
}

void qPlayerHUDScript::Begin()
{

}

void qPlayerHUDScript::Tick()
{
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Player = pCurLevel->FindObjectByName(L"Player");
	qPlayerScript* PlayerScript = Player->GetScript<qPlayerScript>();

	m_FiveCount = PlayerScript->GetFiveDamageCount();
	m_TenCount = PlayerScript->GetTenDamageCount();

	qConstBuffer* pCB = qDevice::GetInst()->GetConstBuffer(CB_TYPE::HUD);

	m_CurPlayerHP = m_MaxPlayerHP - (m_FiveCount * 0.05f + m_TenCount * 0.1f);

	pCB->SetData(&m_CurPlayerHP);

	pCB->Binding();

}

void qPlayerHUDScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qPlayerHUDScript::SaveToFile(FILE* _File)
{
}

void qPlayerHUDScript::LoadFromFile(FILE* _File)
{
}
