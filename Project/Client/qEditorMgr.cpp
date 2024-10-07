#include "pch.h"
#include "qEditorMgr.h"

#include <Engine/components.h>
#include <Engine/qKeyMgr.h>
#include <Engine/qRenderMgr.h>
#include <Engine/qPathMgr.h>
#include <Engine/qEngine.h>
#include <Engine/qDevice.h>

#include "qEditorCameraScript.h"
#include "qGameObjectEx.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#include "EditorUI.h"


qEditorMgr::qEditorMgr()
	: m_hNotifyHandle(nullptr)
{

}

qEditorMgr::~qEditorMgr()
{
	Delete_Vec(m_vecEditorObject);
	Delete_Map(m_mapUI);

	// ImGui Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void qEditorMgr::Init()
{
	CreateEditorObject();

	InitImGui();

	// Content 폴더를 감시하는 커널 오브젝트 생성
	wstring ContentPath = qPathMgr::GetInst()->GetContentPath();
	m_hNotifyHandle = FindFirstChangeNotification(ContentPath.c_str(), true
		, FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME
		| FILE_ACTION_ADDED | FILE_ACTION_REMOVED);
}

void qEditorMgr::Tick()
{
	ShortCut();

	EditorObjectProgress();

	ImGuiProgress();

	ObserveContent();
}


void qEditorMgr::ShortCut()
{
	if (KEY_TAP(KEY::I))
	{
		EditorUI* pUI = FindEditorUI("Inspector");

		if (pUI->IsActive())
			pUI->SetActive(false);
		else
			pUI->SetActive(true);
	}
}


void qEditorMgr::EditorObjectProgress()
{
	for (size_t i = 0; i < m_vecEditorObject.size(); ++i)
	{
		m_vecEditorObject[i]->Tick();
	}

	for (size_t i = 0; i < m_vecEditorObject.size(); ++i)
	{
		m_vecEditorObject[i]->FinalTick();
	}
}




void qEditorMgr::ImGuiTick()
{
	ImGui::ShowDemoWindow();

	for (const auto& pair : m_mapUI)
	{
		pair.second->Tick();
	}
}



