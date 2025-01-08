#include "pch.h"
#include "SkyBoxUI.h"

#include <Engine/qSkyBox.h>
#include "ParamUI.h"

SkyBoxUI::SkyBoxUI()
	: ComponentUI(COMPONENT_TYPE::SKYBOX)
{
}

SkyBoxUI::~SkyBoxUI()
{
}

void SkyBoxUI::Update()
{
	Title();

	qSkyBox* pSkyBox = GetTargetObject()->SkyBox();

	// SkyBox Type
	SKYBOX_TYPE Type = pSkyBox->GetSkyBoxType();

	const char* szItems[] = { "Sphere", "Cube" };
	const char* combo_preview_items = szItems[(UINT)Type];

	ImGui::Text("SkyBox Type");
	ImGui::SameLine(100);
	ImGui::SetNextItemWidth(180);

	if (ImGui::BeginCombo("##SkyBoxTypeCombo", combo_preview_items))
	{
		for (int i = 0; i < 2; ++i)
		{
			const bool is_selected = ((UINT)Type == i);

			if (ImGui::Selectable(szItems[i], is_selected))
			{
				Type = (SKYBOX_TYPE)i;
				pSkyBox->SetSkyBoxType(Type);
			}

			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	Ptr<qTexture> pTex = pSkyBox->GetSkyBoxTexture();

	bool bChange = ParamUI::InputTexture(pTex, "TEXTURE", this, (DELEGATE_1)&SkyBoxUI::ChangeSkybox);

	//if (bChange)
	//	pSkyBox->SetSkyBoxTexture(pTex);
}


#include "ListUI.h"
void SkyBoxUI::ChangeSkybox(DWORD_PTR Param)
{
	// 텍스처 파라미터를 입력받을 재질
	//Ptr<qTexture> pTexture = (qTexture*)Get().Get();

	// 마지막으로 선택한 항목이 무엇인지 ListUI를 통해서 알아냄
	ListUI* pListUI = (ListUI*)Param;
	string strName = pListUI->GetSelectName();
	
	
	qSkyBox* pSkyBox = GetTargetObject()->SkyBox();


	if ("None" == strName)
	{
		pSkyBox->SetSkyBoxTexture(nullptr);
		return;
	}

	wstring strAssetName = wstring(strName.begin(), strName.end());

	Ptr<qTexture> pTex = qAssetMgr::GetInst()->FindAsset<qTexture>(strAssetName);

	assert(pTex.Get());

	pSkyBox->SetSkyBoxTexture(pTex);
	//SaveMaterialToFile();
}
