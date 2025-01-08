#include "pch.h"
#include "LandScapeUI.h"

#include <Engine/qAssetMgr.h>
#include <Engine/qLandScape.h>
#include "ListUI.h"
#include "ParamUI.h"

LandScapeUI::LandScapeUI()
	: ComponentUI(COMPONENT_TYPE::LANDSCAPE)
{
}

LandScapeUI::~LandScapeUI()
{
}

void LandScapeUI::Init()
{
}

void LandScapeUI::Update()
{
	Title();

	qLandScape* pLandScape = GetTargetObject()->LandScape();

	int iFaceX = pLandScape->GetFaceX();
	int iFaceZ = pLandScape->GetFaceZ();


	if (ParamUI::DragInt(&iFaceX, 1.f, "FaceX"))
		pLandScape->SetFace(iFaceX, iFaceZ);
	if (ParamUI::DragInt(&iFaceZ, 1.f, "FaceZ"))
		pLandScape->SetFace(iFaceX, iFaceZ);


	// Mode
	LANDSCAPE_MODE Type = pLandScape->GetMode();

	const char* szItems[] = { "None" ,"HEIGHT MAP", "SPLATING" };
	const char* combo_preview_items = szItems[(UINT)Type];

	ImGui::Text("Mode");
	ImGui::SameLine(120);
	ImGui::SetNextItemWidth(180);

	if (ImGui::BeginCombo("##LandScapeModeCombo", combo_preview_items))
	{
		for (int i = 0; i < 3; ++i)
		{
			const bool is_selected = ((UINT)Type == i);

			if (ImGui::Selectable(szItems[i], is_selected))
			{
				Type = (LANDSCAPE_MODE)i;
				pLandScape->SetMode(Type);
			}

			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	// Brush Scale
	Vec2 vBrushScale = pLandScape->GetBrushScale();

	if (ParamUI::DragVec2(&vBrushScale, 0.05f, "Brush Scale"))
		pLandScape->SetBrushScale(vBrushScale);

	int iWeightIdx = pLandScape->GetWeightIndex();

	if (ParamUI::DragInt(&iWeightIdx, 1, "Weight Index"))
		pLandScape->SetWeightIndex(iWeightIdx);

	// Texture
	Ptr<qTexture> pHeightMap = pLandScape->GetHeightMap();
	Ptr<qTexture> pBrushTex = pLandScape->GetBrushTex();

	ParamUI::InputTexture(pHeightMap, "HeightMap");
	ParamUI::InputTexture(pBrushTex, "Brush Tex", this, (DELEGATE_1)&LandScapeUI::ChangeBrushIndex);
}

void LandScapeUI::ChangeBrushIndex(DWORD_PTR _Param)
{
	// 마지막으로 선택한 항목이 무엇인지 ListUI 를 통해서 알아냄
	ListUI* pListUI = (ListUI*)_Param;
	string strName = pListUI->GetSelectName();

	qLandScape* pLandScape = GetTargetObject()->LandScape();

	if ("None" == strName)
	{
		pLandScape->SetHeightMap(nullptr);
		return;
	}

	wstring strAssetName = wstring(strName.begin(), strName.end());

	Ptr<qTexture> pTex = qAssetMgr::GetInst()->FindAsset<qTexture>(strAssetName);

	assert(pTex.Get());

	pLandScape->SetBrushIndex(pTex);
}
