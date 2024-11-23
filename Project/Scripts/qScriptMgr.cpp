#include "pch.h"
#include "qScriptMgr.h"

#include "qCameraMoveScript.h"
#include "qMissileScript.h"
#include "qPlayerScript.h"
#include "qTestScript.h"

void qScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"qCameraMoveScript");
	_vec.push_back(L"qMissileScript");
	_vec.push_back(L"qPlayerScript");
	_vec.push_back(L"qTestScript");
}

qScript * qScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"qCameraMoveScript" == _strScriptName)
		return new qCameraMoveScript;
	if (L"qMissileScript" == _strScriptName)
		return new qMissileScript;
	if (L"qPlayerScript" == _strScriptName)
		return new qPlayerScript;
	if (L"qTestScript" == _strScriptName)
		return new qTestScript;
	return nullptr;
}

qScript * qScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new qCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new qMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new qPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::TESTSCRIPT:
		return new qTestScript;
		break;
	}
	return nullptr;
}

const wchar_t * qScriptMgr::GetScriptName(qScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"qCameraMoveScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"qMissileScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"qPlayerScript";
		break;

	case SCRIPT_TYPE::TESTSCRIPT:
		return L"qTestScript";
		break;

	}
	return nullptr;
}