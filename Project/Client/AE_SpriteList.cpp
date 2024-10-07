#include "pch.h"
#include "AE_SpriteList.h"

#include "TreeUI.h"
#include "ListUI.h"
#include "qEditorMgr.h"
#include "AE_Detail.h"

AE_SpriteList::AE_SpriteList()
	: m_IsActive(false)
	, m_ListIndex(0)
{
}

AE_SpriteList::~AE_SpriteList()
{
}

void AE_SpriteList::Init()
{
	m_vecAddedSprite.clear();
	m_ListIndex = 0;
	m_IsActive = false;
}

void AE_SpriteList::Update()
{
	if (GetDetail()->GetCurMode()[0] || GetDetail()->GetCurMode()[1])
		m_IsActive = true;
	else
		m_IsActive = false;

	ShowList();
}


void AE_SpriteList::ShowList()
{
	if (!m_IsActive)
		ImGui::BeginDisabled();

	if (ImGui::BeginListBox("##AE_AddedSpriteList", ImVec2(-FLT_MIN - 30.f, 11 * ImGui::GetTextLineHeightWithSpacing())))
	{
		for (size_t i = 0; i < m_vecAddedSprite.size(); ++i)
		{
			const bool is_selected = (m_ListIndex == i);
			path Path = m_vecAddedSprite[i]->GetKey();
			string label = Path.stem().string();
			if (ImGui::Selectable(label.c_str(), is_selected))
			{
				m_ListIndex = i;
			}

			if (is_selected)
			{
				ImGui::SetItemDefaultFocus();
				GetDetail()->SetCurSprite(m_vecAddedSprite[m_ListIndex]);
			}
		}
		ImGui::EndListBox();
	}

	if (m_IsActive)
	{
		if (ImGui::BeginDragDropTarget())
		{
			const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");
			if (payload)
			{
				TreeNode** ppNode = (TreeNode**)payload->Data;
				TreeNode* pNode = *ppNode;

				Ptr<qAsset> pAsset = (qAsset*)pNode->GetData();
				if (ASSET_TYPE::SPRITE == pAsset->GetAssetType())
				{
					m_vecAddedSprite.push_back((qSprite*)pAsset.Get());
					GetDetail()->SetCurSprite(m_vecAddedSprite[m_vecAddedSprite.size() - 1]);
				}
			}
			ImGui::EndDragDropTarget();
		}
	}

	ImGui::SameLine(ImGui::GetWindowSize().x - 30.f);
	ImGui::BeginGroup();
	if (ImGui::ArrowButton("##up", ImGuiDir_Up))
	{
		if (m_ListIndex > 0)
		{
			auto temp = m_vecAddedSprite[m_ListIndex - 1];
			m_vecAddedSprite[m_ListIndex - 1] = m_vecAddedSprite[m_ListIndex];
			m_vecAddedSprite[m_ListIndex] = temp;

			m_ListIndex = m_ListIndex - 1;
		}
	}
	if (ImGui::ArrowButton("##down", ImGuiDir_Down))
	{
		if (m_ListIndex < m_vecAddedSprite.size() - 1)
		{
			auto temp = m_vecAddedSprite[m_ListIndex + 1];
			m_vecAddedSprite[m_ListIndex + 1] = m_vecAddedSprite[m_ListIndex];
			m_vecAddedSprite[m_ListIndex] = temp;

			m_ListIndex = m_ListIndex + 1;
		}
	}
	ImGui::EndGroup();

	ImGui::Text("");
	
	ImGui::SetCursorPosX((ImGui::GetWindowSize().x * 0.5) - 115.f);		// 중간으로 배치
	if (ImGui::Button("ADD", ImVec2(100.f, 22.f)))
	{
		ListUI* pListUI = (ListUI*)qEditorMgr::GetInst()->FindEditorUI("List");
		pListUI->ShowNameOnly(true);
		pListUI->SetName("Sprite");

		vector<string> vecSpriteNames;
		qAssetMgr::GetInst()->GetAssetNames(ASSET_TYPE::SPRITE, vecSpriteNames);
		pListUI->AddList(vecSpriteNames);
		pListUI->AddDelegate(this, (DELEGATE_1)&AE_SpriteList::SelectSprite);
		pListUI->SetActive(true);
	}

	ImGui::SameLine(0.f, 10.f);
	if (ImGui::Button("DELETE", ImVec2(100.f, 22.f)))
	{
		vector<Ptr<qSprite>>::iterator iter = m_vecAddedSprite.begin();
		m_vecAddedSprite.erase(iter + m_ListIndex);
	}

	if (!m_IsActive)
		ImGui::EndDisabled();
}


void AE_SpriteList::SelectSprite(DWORD_PTR _ListUI)
{
	ListUI* pListUI = (ListUI*)_ListUI;
	string strName = pListUI->GetSelectName();

	if (strName == "None")
		return;

	wstring strAssetName = wstring(strName.begin(), strName.end());
	Ptr<qSprite> pSprite = qAssetMgr::GetInst()->FindAsset<qSprite>(strAssetName);

	assert(pSprite.Get());

	m_vecAddedSprite.push_back(pSprite);

}


void AE_SpriteList::SetSpriteToList(vector<Ptr<qSprite>>& _vecSprite)
{
	m_vecAddedSprite.clear();

	for (size_t i = 0; i < _vecSprite.size(); ++i)
	{
		m_vecAddedSprite.push_back(_vecSprite[i]);
	}
}
