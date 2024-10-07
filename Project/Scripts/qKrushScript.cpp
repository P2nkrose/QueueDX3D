#include "pch.h"
#include "qKrushScript.h"

qKrushScript::qKrushScript()
	: qScript((UINT)SCRIPT_TYPE::KRUSHSCRIPT)
{
}

qKrushScript::~qKrushScript()
{
}

void qKrushScript::Begin()
{
}

void qKrushScript::Tick()
{
}

void qKrushScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qKrushScript::SaveToFile(FILE* _File)
{
}

void qKrushScript::LoadFromFile(FILE* _File)
{
}
