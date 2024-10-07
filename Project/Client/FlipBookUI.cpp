#include "pch.h"
#include "FlipBookUI.h"

#include <Engine/qFlipBook.h>

FlipBookUI::FlipBookUI()
	: AssetUI(ASSET_TYPE::FLIPBOOK)
	, m_FlipBookIdx(0)
{
}

FlipBookUI::~FlipBookUI()
{
}

void FlipBookUI::Update()
{
	Title();

	Ptr<qFlipBook> pFlipBook = (qFlipBook*)GetAsset().Get();

	// ÀÌ¹ÌÁö
	//ImVec2 uv_min = ImVec2(0.0f, 0.0f);
	//ImVec2 uv_max = ImVec2(1.0f, 1.0f);
	//
	//ImVec4 tint_col = ImVec4(1.f, 1.f, 1.f, 1.f);
	//ImVec4 border_col = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
	//ImGui::Image(pFlipBook->GetSprite(m_FlipBookIdx).Get(), ImVec2(150, 150), uv_min, uv_max, tint_col, border_col);


	OutputAssetName();

}
