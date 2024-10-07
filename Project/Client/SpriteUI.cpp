#include "pch.h"
#include "SpriteUI.h"

#include <Engine/qTexture.h>
#include <Engine/qAssetMgr.h>

#include <Engine/qSprite.h>
#include <Engine/qTexture.h>

SpriteUI::SpriteUI()
	: AssetUI(ASSET_TYPE::SPRITE)
{
}

SpriteUI::~SpriteUI()
{
}

void SpriteUI::Update()
{
	Title();

	ImGui::Text("");

	Sprite();


}

void SpriteUI::Sprite()
{
	// 스프라이트 이름
	OutputAssetName();

	ImGui::Text("");
	ImGui::Text("                     ");
	ImGui::SameLine();

	Ptr<qSprite> pTexture = (qSprite*)GetAsset().Get();

	ImVec2 LTUV = ImVec2(pTexture->GetLeftTopUV().x, pTexture->GetLeftTopUV().y);
	ImVec2 Slice = ImVec2(pTexture->GetSliceUV().x, pTexture->GetSliceUV().y);
	ImVec2 Resolution = ImVec2(pTexture->GetAtlasTexture()->Width(), pTexture->GetAtlasTexture()->Height());

	float fWidth = pTexture->GetAtlasTexture()->Width();
	float fHeight = pTexture->GetAtlasTexture()->Height();

	ImVec2 LTSize = ImVec2(Resolution.x * LTUV.x, Resolution.y * LTUV.y);
	ImVec2 SliceSize = ImVec2(Resolution.x * Slice.x, Resolution.y * Slice.y);
	ImVec2 RBSize = ImVec2(LTSize.x + SliceSize.x, LTSize.y + SliceSize.y);

	ImVec2 RBUV = ImVec2(RBSize.x / Resolution.x, RBSize.y / Resolution.y);

	Vec2 OffsetUV = Vec2(pTexture->GetOffsetUV().x, pTexture->GetOffsetUV().y);

	//ImVec2 OffsetUV = ImVec2(pTexture->GetOffsetUV().x, pTexture->GetOffsetUV().y);

	Vec2 OffSet = Vec2(OffsetUV.x * fWidth, OffsetUV.y * fHeight);

	ImVec2 BGUV = ImVec2(pTexture->GetBackgroundUV().x, pTexture->GetBackgroundUV().y);

	ImVec2 BGSize = ImVec2(Resolution.x * BGUV.x, Resolution.y * BGUV.y);

	ImVec4 tint_col = ImVec4(1.f, 1.f, 1.f, 1.f);
	ImVec4 border_col = ImVec4(0.7f, 0.7f, 0.7f, 1.f);

	ImGui::Image(pTexture->GetAtlasTexture()->GetSRV().Get(), ImVec2(150, 150), ImVec2(LTUV.x - OffsetUV.x, LTUV.y - OffsetUV.y), ImVec2(RBUV.x - OffsetUV.x, RBUV.y - OffsetUV.y), tint_col, border_col);

	ImGui::Text("");
	ImGui::Separator();
	ImGui::Text("");

	ImGui::Text("Left Top");
	ImGui::SameLine(105);
	ImGui::SetNextItemWidth(300.f);
	ImGui::InputFloat2("##LeftTop", (float*)&LTSize);
	
	ImGui::Text("Slice");
	ImGui::SameLine(105);
	ImGui::SetNextItemWidth(300.f);
	ImGui::InputFloat2("##Slice", (float*)&SliceSize);

	ImGui::Text("Offset");
	ImGui::SameLine(105);
	ImGui::SetNextItemWidth(300.f);
	ImGui::DragFloat2("##Offset", OffSet);

	ImGui::Text("BackGround");
	ImGui::SameLine(105);
	ImGui::SetNextItemWidth(300);
	ImGui::InputFloat2("##BackGround", (float*)&BGSize);

	pTexture->SetLeftTop(Vec2(LTSize.x, LTSize.y));
	pTexture->SetSlice(Vec2(SliceSize.x, SliceSize.y));
	pTexture->SetOffset(Vec2(OffSet.x, OffSet.y));
	pTexture->SetBackground(Vec2(BGSize.x, BGSize.y));


	ImGui::Text("");

	ImGui::Separator();

	ImGui::Text("");


	// 스프라이트 저장

	ImGui::Text("Add Prefab Name");
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

		// wb
		Ptr<qSprite> pSprite = new qSprite;
		wstring strName = wstring(m_SpriteName.begin(), m_SpriteName.end());

		pTexture->Create(pTexture->GetAtlasTexture(), Vec2(LTSize.x - OffsetUV.x, LTSize.y - OffsetUV.y), Vec2(SliceSize.x - OffsetUV.x, SliceSize.y - OffsetUV.y));
		pTexture->SetBackground(Vec2(BGSize.x, BGSize.y));

		pTexture->SetRelativePath(wstring(L"sprite\\") + strName + L".sprite");
		qAssetMgr::GetInst()->AddAsset(strName, pTexture);

		wstring ContentPath = qPathMgr::GetInst()->GetContentPath();

		pTexture->Save(ContentPath + L"sprite\\" + strName + L".sprite");

	}

}



