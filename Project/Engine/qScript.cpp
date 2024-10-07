#include "pch.h"
#include "qScript.h"

qScript::qScript(UINT _ScriptType)
	: qComponent(COMPONENT_TYPE::SCRIPT)
	, m_ScriptType(_ScriptType)
{
}

qScript::~qScript()
{
}

void qScript::Instantiate(Ptr<qPrefab> _Pref, int _LayerIdx, Vec3 _WorldPos, const wstring& _Name)
{
	qGameObject* pInst = _Pref->Instantiate();

	pInst->SetName(_Name);
	pInst->Transform()->SetRelativePos(_WorldPos);

	CreateObject(pInst, _LayerIdx);
}
