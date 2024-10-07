#include "pch.h"
#include "AnimationEditor.h"

#include "qEditorMgr.h"

#include "AE_Detail.h"
#include "AE_Preview.h"
#include "AE_SpriteList.h"

AnimationEditor::AnimationEditor()
	: m_Preview(nullptr)
	, m_SpriteList(nullptr)
	, m_Detail(nullptr)
{
	UseMenuBar(true);
}

AnimationEditor::~AnimationEditor()
{
}

void AnimationEditor::Init()
{
	m_Preview = (AE_Preview*)qEditorMgr::GetInst()->FindEditorUI("AE_Preview");
	m_SpriteList = (AE_SpriteList*)qEditorMgr::GetInst()->FindEditorUI("AE_SpriteList");
	m_Detail = (AE_Detail*)qEditorMgr::GetInst()->FindEditorUI("AE_Detail");

	m_Preview->SetMove(true);
	m_SpriteList->SetMove(true);
	m_Detail->SetMove(true);

	m_Preview->m_Owner = this;
	m_SpriteList->m_Owner = this;
	m_Detail->m_Owner = this;

}



void AnimationEditor::Update()
{
	if (ImGui::BeginMenuBar())
	{
		Window();

		ImGui::EndMenuBar();
	}
}

void AnimationEditor::Activate()
{
	m_Preview->SetActive(true);
	m_SpriteList->SetActive(true);
	m_Detail->SetActive(true);
}

void AnimationEditor::Deactivate()
{
	m_Preview->SetActive(false);
	m_SpriteList->SetActive(false);
	m_Detail->SetActive(false);
}

void AnimationEditor::Window()
{
	if (ImGui::BeginMenu("Window"))
	{
		bool Preview = m_Preview->IsActive();
		bool Detail = m_Detail->IsActive();
		bool SpriteView = m_SpriteList->IsActive();

		if (ImGui::MenuItem("Preview", nullptr, &Preview))
		{
			m_Preview->SetActive(Preview);
		}

		if (ImGui::MenuItem("SpriteView", nullptr, &SpriteView))
		{
			m_SpriteList->SetActive(SpriteView);
		}

		if (ImGui::MenuItem("Detail", nullptr, &Detail))
		{
			m_Detail->SetActive(Detail);
		}

		ImGui::EndMenu();
	}
}


wstring AnimationEditor::GetAssetKey(ASSET_TYPE _Type, const wstring& _Format)
{
	wstring Key;

	Key = wstring(L"flipbook\\") + _Format + L" %d.flip";
	
	wchar_t szKey[255] = {};
	wstring FilePath = qPathMgr::GetInst()->GetContentPath();

	for (UINT i = 0; i < 0xffffffff; ++i)
	{
		swprintf_s(szKey, 255, Key.c_str(), i);

		if (false == std::filesystem::exists(FilePath + szKey))
		{
			break;
		}
	}

	return szKey;
}

