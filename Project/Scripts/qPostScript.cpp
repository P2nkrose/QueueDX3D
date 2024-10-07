#include "pch.h"
#include "qPostScript.h"

qPostScript::qPostScript()
	: qScript((UINT)SCRIPT_TYPE::POSTSCRIPT)
{
}

qPostScript::~qPostScript()
{
}

void qPostScript::Begin()
{
}

void qPostScript::Tick()
{
}

void qPostScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qPostScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qPostScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qPostScript::SaveToFile(FILE* _File)
{
}

void qPostScript::LoadFromFile(FILE* _File)
{
}
