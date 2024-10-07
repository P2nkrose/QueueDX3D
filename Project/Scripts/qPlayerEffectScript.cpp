#include "pch.h"
#include "qPlayerEffectScript.h"

qPlayerEffectScript::qPlayerEffectScript()
	: qScript((UINT)SCRIPT_TYPE::PLAYEREFFECTSCRIPT)
{
}

qPlayerEffectScript::~qPlayerEffectScript()
{
}

void qPlayerEffectScript::Begin()
{
}

void qPlayerEffectScript::Tick()
{
}

void qPlayerEffectScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qPlayerEffectScript::SaveToFile(FILE* _File)
{
}

void qPlayerEffectScript::LoadFromFile(FILE* _File)
{
}
