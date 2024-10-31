#include "pch.h"
#include "qTestScript.h"

qTestScript::qTestScript()
	: qScript((UINT)SCRIPT_TYPE::TESTSCRIPT)
{
}

qTestScript::~qTestScript()
{
}

void qTestScript::Begin()
{
}

void qTestScript::Tick()
{
}

void qTestScript::SaveToFile(FILE* _File)
{
}

void qTestScript::LoadFromFile(FILE* _File)
{
}
