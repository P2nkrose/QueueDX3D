#include "pch.h"
#include "qDeathSoulScript.h"

qDeathSoulScript::qDeathSoulScript()
	: qScript((UINT)SCRIPT_TYPE::DEATHSOULSCRIPT)
{
}

qDeathSoulScript::~qDeathSoulScript()
{
}

void qDeathSoulScript::Begin()
{
}

void qDeathSoulScript::Tick()
{
}

void qDeathSoulScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qDeathSoulScript::SaveToFile(FILE* _File)
{
}

void qDeathSoulScript::LoadFromFile(FILE* _File)
{
}
