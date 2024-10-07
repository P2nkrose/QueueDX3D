#include "pch.h"
#include "FlipBookComUI.h"

#include "qEditorMgr.h"
#include "TreeUI.h"
#include "ListUI.h"


#include <Engine/qSprite.h>
#include <Engine/qTexture.h>
#include <Engine/qFlipBook.h>




FlipBookComUI::FlipBookComUI()
	: ComponentUI(COMPONENT_TYPE::FLIPBOOKCOMPONENT)
	, m_FBCom(nullptr)
	, m_UIHeight(0)
	, m_AccTime(0)
	, m_CurSpriteIndex(0)
	, m_MaxSpriteIndex(0)
	, m_Playing(false)
	, m_Repeat(false)
{
}

FlipBookComUI::~FlipBookComUI()
{
}

void FlipBookComUI::Update()
{
	m_UIHeight = 0;
	
	Title();

	m_UIHeight += (int)ImGui::GetItemRectSize().y;

	m_FBCom = GetTargetObject()->FlipBookComponent();
	m_CurFB = m_FBCom->GetCurFlipBook();
	if (nullptr != m_CurFB.Get())
	{
		m_CurSprite = m_CurFB->GetSprite(m_CurSpriteIndex);
		m_Repeat = m_FBCom->GetRepeat();
	}

	vector<Ptr<qFlipBook>> vFB = m_FBCom->GetVecFlipBook();


	ImGui::Text("Current FlipBook");
	ImGui::SameLine(120);
	ImGui::SetNextItemWidth(230);

	string Key;

	if (nullptr == m_CurFB.Get())
	{
		Key = "None";
	}
	else
	{
		Key = string(m_CurFB.Get()->GetKey().begin(), m_CurFB.Get()->GetKey().end());
	}

	ImGui::InputText("##FlipBookKey", (char*)Key.c_str(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);
	m_UIHeight += (int)ImGui::GetItemRectSize().y;


	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");
		if (payload)
		{
			TreeNode** ppNode = (TreeNode**)payload->Data;
			TreeNode* pNode = *ppNode;

			Ptr<qAsset> pAsset = (qAsset*)pNode->GetData();
			if (ASSET_TYPE::FLIPBOOK == pAsset->GetAssetType())
			{
				m_FBCom->SetCurFlipBook((qFlipBook*)pAsset.Get());
			}
		}
		ImGui::EndDragDropTarget();
	}

	ImGui::SameLine();

	if (ImGui::Button("##FlipBookBtn", ImVec2(18.f, 18.f)))
	{
		ListUI* pListUI = (ListUI*)qEditorMgr::GetInst()->FindEditorUI("List");
		pListUI->ShowNameOnly(true);
		pListUI->SetName("FlipBook");
		
		vector<string> vecFlipBookNames;
		for (size_t i = 0; i < vFB.size(); ++i)
		{
			if (nullptr == vFB[i].Get())
				continue;

			string FlipBookName = string(vFB[i].Get()->GetKey().begin(), vFB[i].Get()->GetKey().end());
			vecFlipBookNames.push_back(FlipBookName);
		}
		
		pListUI->AddList(vecFlipBookNames);
		pListUI->AddDelegate(this, (DELEGATE_1)&FlipBookComUI::SelectFlipBook);
		pListUI->SetActive(true);
	}
	m_UIHeight += (int)ImGui::GetItemRectSize().y;

	if (nullptr == m_FBCom || nullptr == m_CurFB.Get())
	{
		SetChildSize(ImVec2(0.f, (float)m_UIHeight));
		return;
	}

	ImGui::Text("");
	m_UIHeight += (int)ImGui::GetItemRectSize().y;


	// Show Current FlipBook Sprite
	ShowFlipBookSprite(m_CurFB.Get(), m_CurSpriteIndex);
	if (m_Playing)
	{
		m_AccTime += EngineDT;
	}

	ImGui::SetCursorPosX((ImGui::GetWindowSize().x * 0.5f) - 100.f);
	if (ImGui::Button("PLAY", ImVec2(95.f, 18.f)))
	{
		m_Playing = true;
	}

	ImGui::SameLine((ImGui::GetWindowSize().x * 0.5f) + 5.f);
	if (ImGui::Button("STOP", ImVec2(95.f, 18.f)))
	{
		m_Playing = false;
		m_CurSpriteIndex = 0;
		m_AccTime = 0;
	}

	m_UIHeight += (int)ImGui::GetItemRectSize().y;

	ImGui::Text("");
	m_UIHeight += (int)ImGui::GetItemRectSize().y;


	// Current Frame Index / Sprite
	ImGui::Text("Current Frame");
	ImGui::SameLine(120);
	ImGui::SetNextItemWidth(30.f);
	ImGui::InputInt("##FlipBookFrmIdx", (int*)&m_CurSpriteIndex, 0, 0, ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);

	ImGui::SameLine(155.f);
	ImGui::SetNextItemWidth(200.f);
	string spriteKey = string(m_CurSprite->GetKey().begin(), m_CurSprite->GetKey().end());
	ImGui::InputText("##SpriteKey", (char*)spriteKey.c_str(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);
	m_UIHeight += (int)ImGui::GetItemRectSize().y;

	ImGui::SameLine(360.f);
	ImGui::PushButtonRepeat(true);
	if (ImGui::ArrowButton("##left", ImGuiDir_Left))
	{
		if (0 == m_CurSpriteIndex)
			m_CurSpriteIndex = 0;
		else
			m_CurSpriteIndex--;
	}

	ImGui::SameLine(0.0f, 5.f);
	if (ImGui::ArrowButton("##right", ImGuiDir_Right))
	{
		if (m_CurSpriteIndex >= m_CurFB->GetMaxFrameCount() - 1)
			m_CurSpriteIndex = m_CurFB->GetMaxFrameCount() - 1;
		else
			m_CurSpriteIndex++;
	}

	ImGui::PopButtonRepeat();
	m_UIHeight += (int)ImGui::GetItemRectSize().y;


	// FPS
	ImGui::Text("FPS");
	float FPS = m_FBCom->GetFPS();
	ImGui::SameLine(120);
	ImGui::SetNextItemWidth(235.f);
	ImGui::DragFloat("##FlipBookFPS", &FPS, 0.1f);
	m_UIHeight += (int)ImGui::GetItemRectSize().y;

	m_FBCom->SetFPS(FPS);

	// Repeat
	ImGui::Text("Repeat");
	ImGui::SameLine(120);
	if (ImGui::Checkbox("##FlipBookRepeat", &m_Repeat))
	{
		m_FBCom->SetRepeat(m_Repeat);
	}

	m_UIHeight += (int)ImGui::GetItemRectSize().y;

	SetChildSize(ImVec2(0.f, (float)m_UIHeight));
}

void FlipBookComUI::SelectFlipBook(DWORD_PTR _ListUI)
{
	qFlipBookComponent* pFlipBookCom = GetTargetObject()->FlipBookComponent();

	ListUI* pListUI = (ListUI*)_ListUI;
	string strName = pListUI->GetSelectName();

	if ("None" == strName)
	{
		pFlipBookCom->SetCurFlipBook(nullptr);
		return;
	}

	wstring strAssetName = wstring(strName.begin(), strName.end());
	Ptr<qFlipBook> pFlipBook = qAssetMgr::GetInst()->FindAsset<qFlipBook>(strAssetName);

	assert(pFlipBook.Get());

	pFlipBookCom->SetCurFlipBook(pFlipBook);
}


void FlipBookComUI::ShowFlipBookSprite(Ptr<qFlipBook> _CurFlipBook, int _CurIndex)
{
	m_MaxSpriteIndex = m_FBCom->GetCurFlipBook()->GetMaxFrameCount();

	float MaxTime = 1.f / m_FBCom->GetFPS();
	if (MaxTime < m_AccTime)
	{
		m_AccTime -= MaxTime;
		++m_CurSpriteIndex;

		if (m_CurFB->GetMaxFrameCount() <= m_CurSpriteIndex)
		{
			if (m_Repeat)
			{
				m_CurSpriteIndex = 0;
			}
			else
			{
				m_Playing = false;
				m_CurSpriteIndex = m_MaxSpriteIndex - 1;
			}
		}
	}

	m_CurSprite = m_CurFB->GetSprite(m_CurSpriteIndex);
	Ptr<qTexture> pTexture = m_CurSprite->GetAtlasTexture();

	// Image Size
	ImVec2 crop = ImVec2(m_CurSprite->GetBackgroundUV().x * pTexture->Width()
					   , m_CurSprite->GetBackgroundUV().y * pTexture->Height());

	ImVec2 frameSize = ImVec2(200.f, 200.f);
	if (frameSize.x < crop.x || frameSize.y < crop.y)
	{
		float ratio = crop.x / frameSize.x;
		ratio = 1 / ratio;

		crop.x *= ratio;
		crop.y *= ratio;
	}

	ImVec2 uv_min = ImVec2(m_CurSprite->GetLeftTopUV().x, m_CurSprite->GetLeftTopUV().y);
	ImVec2 uv_max = ImVec2(m_CurSprite->GetLeftTopUV().x + m_CurSprite->GetSliceUV().x
		, m_CurSprite->GetLeftTopUV().y + m_CurSprite->GetSliceUV().y);

	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 border_col = ImVec4(0.7f, 0.7f, 0.7f, 0.7f);
	ImGui::SetCursorPosX((ImGui::GetWindowSize().x - frameSize.x) * 0.5f);
	ImGui::Image(pTexture->GetSRV().Get(), crop, uv_min, uv_max, tint_col, border_col);
	m_UIHeight += (int)ImGui::GetItemRectSize().y;
}
