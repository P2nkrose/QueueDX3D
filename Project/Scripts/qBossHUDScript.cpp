#include "pch.h"
#include "qBossHUDScript.h"

#include <Engine/qSprite.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>
#include <Engine/qDevice.h>
#include <Engine/qConstBuffer.h>
#include <Engine/qGameObject.h>

#include <Scripts/qBossScript.h>

qBossHUDScript::qBossHUDScript()
	: qScript((UINT)SCRIPT_TYPE::BOSSHUDSCRIPT)
	, m_MaxBossHP(1.f)
	, m_CurBossHP(1.f)
	, m_DamageHP(0.f)
	, m_10Count(0)
	, m_20Count(0)
	, m_30Count(0)
	, m_40Count(0)
	, m_50Count(0)
{
}

qBossHUDScript::~qBossHUDScript()
{
}

void qBossHUDScript::Begin()
{
}

void qBossHUDScript::Tick()
{
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Boss = pCurLevel->FindObjectByName(L"Boss");
	qBossScript* BossScript = Boss->GetScript<qBossScript>();

	m_10Count = BossScript->Get10Damagecount();
	m_20Count = BossScript->Get20Damagecount();
	m_30Count = BossScript->Get30Damagecount();
	m_40Count = BossScript->Get40Damagecount();
	m_50Count = BossScript->Get50Damagecount();

	qConstBuffer* pCB = qDevice::GetInst()->GetConstBuffer(CB_TYPE::BOSSHUD);

	m_CurBossHP = m_MaxBossHP - (m_10Count * 0.025f + m_20Count * 0.05f + m_30Count * 0.075f + m_40Count * 0.1f + m_50Count * 0.125f);
	
	pCB->SetData(&m_CurBossHP);

	pCB->Binding();
}

void qBossHUDScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qBossHUDScript::SaveToFile(FILE* _File)
{
}

void qBossHUDScript::LoadFromFile(FILE* _File)
{
}
