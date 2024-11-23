#pragma once

#include <vector>
#include <string>

enum SCRIPT_TYPE
{
	CAMERAMOVESCRIPT,
	MISSILESCRIPT,
	PLAYERSCRIPT,
	TESTSCRIPT,
};

using namespace std;

class qScript;

class qScriptMgr
{
public:
	static void GetScriptInfo(vector<wstring>& _vec);
	static qScript * GetScript(const wstring& _strScriptName);
	static qScript * GetScript(UINT _iScriptType);
	static const wchar_t * GetScriptName(qScript * _pScript);
};
