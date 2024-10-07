#include "pch.h"
#include "SE_Detail.h"
#include "SE_AtlasView.h"

#include "qEditorMgr.h"
#include "ListUI.h"
#include "TreeUI.h"

#include <Engine/qAssetMgr.h>
#include <Engine/qPathMgr.h>
#include <Engine/qAsset.h>
#include <Engine/qSprite.h>

static char BufferSpriteName[255] = "";

SE_Detail::SE_Detail()
	: m_CurIndex(0)
{
}

SE_Detail::~SE_Detail()
{
}

void SE_Detail::Init()
{
}

void SE_Detail::Update()
{
	ImGui::SeparatorText("Select Atlas Info");
	Atlas();
	AtlasInfo();


	SpriteInfo();

	//ImGui::SeparatorText("List of Sprite to Add");
	//SpriteList();
	//
	//ImGui::Text("");


	CreateSprite();
}

void SE_Detail::Atlas()
{
	ImGui::Text("");

	if (nullptr != m_AtlasTex)
	{
		Path = m_AtlasTex.Get()->GetKey();
		TexName = Path.stem().string();
	}

	//TexName = string(m_AtlasTex->GetKey().begin(), m_AtlasTex->GetKey().end());

	ImGui::Text("Atlas Texture Name");
	ImGui::SameLine(150);
	ImGui::SetNextItemWidth(200.f);
	ImGui::InputText("##AtlasTex", (char*)TexName.c_str(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);

	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");
		if (payload)
		{
			TreeNode** ppNode = (TreeNode**)payload->Data;
			TreeNode* pNode = *ppNode;

			Ptr<qAsset> pAsset = (qAsset*)pNode->GetData();
			if (ASSET_TYPE::TEXTURE == pAsset->GetAssetType())
			{
				SetAtlasTex((qTexture*)pAsset.Get());
			}
		}

		ImGui::EndDragDropTarget();
	}

	ImGui::SameLine();
	if (ImGui::Button("Select", ImVec2(50.f, 19.f)))
	{
		ListUI* pListUI = (ListUI*)qEditorMgr::GetInst()->FindEditorUI("List");
		pListUI->SetName("Texture");
		vector<string> vecTexNames;
		qAssetMgr::GetInst()->GetAssetNames(ASSET_TYPE::TEXTURE, vecTexNames);
		pListUI->AddList(vecTexNames);
		pListUI->AddDelegate(this, (DELEGATE_1)&SE_Detail::SelectTexture);
		pListUI->SetActive(true);
	}
}

void SE_Detail::AtlasInfo()
{
	// ÇØ»óµµ
	UINT width = 0;
	UINT height = 0;

	if (nullptr != m_AtlasTex)
	{
		width = m_AtlasTex->Width();
		height = m_AtlasTex->Height();
	}

	char buff[50] = {};
	sprintf_s(buff, "%d", width);
	ImGui::Text("Width");
	ImGui::SameLine(150);
	ImGui::SetNextItemWidth(200.f);
	ImGui::InputText("##TextureWidth", buff, 50, ImGuiInputTextFlags_ReadOnly);

	sprintf_s(buff, "%d", height);
	ImGui::Text("Height");
	ImGui::SameLine(150);
	ImGui::SetNextItemWidth(200.f);
	ImGui::InputText("##TextureHeight", buff, 50, ImGuiInputTextFlags_ReadOnly);

	// leftTop
	// slice
	// background
	// offset
	// Save     Load
}

void SE_Detail::SpriteInfo()
{

	if (nullptr != m_AtlasTex)
	{
		ImGui::Text("");
		ImGui::SeparatorText("Select Sprite Info");
		ImGui::Text("");


		LeftTop = GetAtlasView()->GetLeftTop();
		RightBottom = GetAtlasView()->GetRightBottom();

		//path Path = m_AtlasTex.Get()->GetKey();
		//string strSpriteName = Path.stem().string();
		//strSpriteName += "_" + std::to_string(m_vecAddSprite.size());
		//
		//ImGui::Text("Sprite Name");
		//ImGui::SameLine(150);
		//ImGui::SetNextItemWidth(200.f);
		//ImGui::InputTextWithHint("##SpriteName", (char*)strSpriteName.c_str(), BufferSpriteName, 255);
	}


	// BackGround
	ImVec2 SliceSize = ImVec2(RightBottom.x - LeftTop.x, RightBottom.y - LeftTop.y);

	//if (m_BackGround.x < SliceSize.x || m_BackGround.y < SliceSize.y)
	//{
	//	float size = SliceSize.x < SliceSize.y ? SliceSize.y : SliceSize.x;
	//	m_BackGround = ImVec2(size, size);
	//}

	//m_BackGround = SliceSize;
	m_BackGround = ImVec2(770.f, 457.f);

	if (SliceSize.x == 0 || SliceSize.y == 0)
	{
		LeftTop = ImVec2(0, 0);
		RightBottom = ImVec2(0, 0);
	}








	// Sprite Image
	if (SliceSize.x != 0 && SliceSize.y != 0)
	{
		// wb
		m_CurSprite = new qSprite;
		wstring strName = wstring(m_SpriteName.begin(), m_SpriteName.end());

		float Slice[] = { RightBottom.x - LeftTop.x, RightBottom.y - LeftTop.y };
		m_CurSprite->Create(m_AtlasTex, Vec2(LeftTop.x, LeftTop.y), Vec2(Slice));
		m_CurSprite->SetBackground(Vec2(m_BackGround.x, m_BackGround.y));

		ImVec2 crop = ImVec2(m_CurSprite->GetBackgroundUV().x * m_AtlasTex->Width()
			, m_CurSprite->GetBackgroundUV().y * m_AtlasTex->Height());

		ImVec2 frameSize = ImVec2(200.f, 200.f);
		if (frameSize.x < crop.x || frameSize.y < crop.y)
		{
			float ratio = crop.x / frameSize.x;
			ratio = 1 / ratio;

			crop.x *= ratio;
			crop.y *= ratio;
		}
		

		// Image
		ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ImVec4 border_col = ImVec4(0.7f, 0.7f, 0.7f, 0.7f);
		ImVec2 Resolution = ImVec2(m_AtlasTex->Width(), m_AtlasTex->Height());
		ImVec2 LTUV = ImVec2(LeftTop.x / Resolution.x , LeftTop.y / Resolution.y);
		ImVec2 RBUV = ImVec2(RightBottom.x / Resolution.x, RightBottom.y / Resolution.y);
		ImGui::SetCursorPosX((ImGui::GetWindowSize().x - crop.x) * 0.5f);
		ImGui::Image(m_AtlasTex->GetSRV().Get(), crop, LTUV, RBUV, tint_col, border_col);

		ImGui::Text("");

		ImGui::Text("Left Top");
		ImGui::SameLine(150);
		float LT[] = { LeftTop.x, LeftTop.y };
		ImGui::SetNextItemWidth(200.f);
		ImGui::InputFloat2("##LT", LT);


		ImGui::Text("Slice");
		ImGui::SameLine(150);
		ImGui::SetNextItemWidth(200.f);
		ImGui::InputFloat2("##Slice", Slice);

		ImGui::Text("Background");
		ImGui::SameLine(150);
		float Background[] = { m_BackGround.x, m_BackGround.y };
		ImGui::SetNextItemWidth(200.f);
		ImGui::InputFloat2("##Background", Background);



		// Create Sprite
		ImGui::Text("");
		ImGui::SeparatorText("Create Sprite");
		ImGui::Text("");

		ImGui::Text("New Sprite Name");
		ImGui::SameLine(150);
		ImGui::SetNextItemWidth(200.f);

		char szName[255] = {};

		if (ImGui::InputText("##Sprite Name", szName, 255))
		{
			m_SpriteName = szName;
		}

		ImGui::SameLine();
		if (ImGui::Button("Create", ImVec2(50.f, 19.f)))
		{

			m_CurSprite->SetRelativePath(wstring(L"sprite\\") + strName + L".sprite");
			qAssetMgr::GetInst()->AddAsset(strName, m_CurSprite);

			wstring ContentPath = qPathMgr::GetInst()->GetContentPath();

			m_CurSprite->Save(ContentPath + L"sprite\\" + strName + L".sprite");

		}



	}
		
	
	




	//if (SliceSize.x != 0 && SliceSize.y != 0)
	//{
	//	// Create Sprite
	//	m_CurSprite = new qSprite;
	//	Vec2 vSpriteLT = { LeftTop.x, LeftTop.y };
	//	Vec2 vSpriteSize = { SliceSize.x, SliceSize.y };

	//	m_CurSprite->Create(m_AtlasTex, vSpriteLT, vSpriteSize);
	//	m_CurSprite->SetBackground(Vec2(m_BackGround.x, m_BackGround.y));


	//}
	
}

void SE_Detail::SpriteList()
{
}

void SE_Detail::CreateSprite()
{
	
}


void SE_Detail::SetAtlasTex(Ptr<qTexture> _Tex)
{
	m_AtlasTex = _Tex;
	GetAtlasView()->SetAtlasTex(m_AtlasTex);
}


void SE_Detail::SelectTexture(DWORD_PTR _ListUI)
{
	ListUI* pListUI = (ListUI*)_ListUI;
	string strName = pListUI->GetSelectName();

	if (strName == "None")
	{
		m_AtlasTex = nullptr;
		return;
	}

	wstring strAssetName = wstring(strName.begin(), strName.end());

	Ptr<qTexture> pTex = qAssetMgr::GetInst()->FindAsset<qTexture>(strAssetName);

	assert(pTex.Get());

	SetAtlasTex(pTex);
}


