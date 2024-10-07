#pragma once

#include <Engine/singleton.h>

class qGameObject;
class EditorUI;

class qEditorMgr : public qSingleton<qEditorMgr>
{
	SINGLE(qEditorMgr);

public:
	void Init();
	void Tick();

public:
	EditorUI* FindEditorUI(const string& _Name);

private:

	void ShortCut();

	void CreateEditorObject();
	void EditorObjectProgress();

	void InitImGui();
	void ObserveContent();
	void ImGuiProgress();
	void ImGuiTick();
	void CreateEditorUI();



private:
	vector<qGameObject*>		m_vecEditorObject;
	map<string, EditorUI*>		m_mapUI;

	HANDLE						m_hNotifyHandle;
};

