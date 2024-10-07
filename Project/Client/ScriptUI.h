#pragma once
#include "ComponentUI.h"

#include <Scripts/qScriptMgr.h>
#include <Engine/qScript.h>

#include "ParamUI.h"

class ScriptUI : public ComponentUI
{
public:
	ScriptUI();
	~ScriptUI();

public:
	virtual void Update() override;

public:
	void SetTargetScript(qScript* _Script);
	qScript* GetTargetScript() { return m_Script; }


private:
	void SelectPrefab(DWORD_PTR _ListUI);

private:
	class qScript*			m_Script;

	UINT					m_UIHeight;

	Ptr<qPrefab>*			m_SelectedPrefab;
};

