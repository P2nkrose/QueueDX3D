#include "pch.h"
#include "ParamUI.h"

#include <Engine/qAssetMgr.h>

#include "ImGui/imgui.h"

#include "qEditorMgr.h"
#include "ListUI.h"

UINT ParamUI::g_ID = 0;


// Scalar Parameter

bool ParamUI::InputInt(int* _Data, const string& _Desc)
{
	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(100);

	char szID[255] = {};
	sprintf_s(szID, 255, "##InputInt%d", g_ID++);

	if (ImGui::InputInt(szID, _Data, 0))
	{
		return true;
	}

	return false;
}

bool ParamUI::DragInt(int* _Data, float _Step, const string& _Desc)
{
	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(100);

	char szID[255] = {};
	sprintf_s(szID, 255, "##DragInt%d", g_ID++);

	if (ImGui::DragInt(szID, _Data, _Step))
	{
		return true;
	}

	return false;
}

bool ParamUI::InputFloat(float* _Data, const string& _Desc)
{
	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(100);

	char szID[255] = {};
	sprintf_s(szID, 255, "##InputFloat%d", g_ID++);

	if (ImGui::InputFloat(szID, _Data, 0))
	{
		return true;
	}

	return false;
}

bool ParamUI::DragFloat(float* _Data, float _Step, const string& _Desc)
{
	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(100);

	char szID[255] = {};
	sprintf_s(szID, 255, "##DragFloat%d", g_ID++);

	if (ImGui::DragFloat(szID, _Data, _Step))
	{
		return true;
	}

	return false;
}

bool ParamUI::InputVec2(Vec2* _Data, const string& _Desc)
{
	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(100);

	char szID[255] = {};
	sprintf_s(szID, 255, "##InputVec2%d", g_ID++);

	if (ImGui::InputFloat2(szID, *_Data, 0))
	{ 
		return true;
	}

	return false;
}

bool ParamUI::DragVec2(Vec2* _Data, float _Step, const string& _Desc)
{
	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(100);

	char szID[255] = {};
	sprintf_s(szID, 255, "##DragVec2%d", g_ID++);

	if (ImGui::DragFloat2(szID, *_Data, _Step))
	{
		return true;
	}

	return false;
}

bool ParamUI::InputVec4(Vec4* _Data, const string& _Desc)
{
	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(100);

	char szID[255] = {};
	sprintf_s(szID, 255, "##InputVec4%d", g_ID++);

	if (ImGui::InputFloat4(szID, *_Data, 0))
	{
		return true;
	}

	return false;
}

bool ParamUI::DragVec4(Vec4* _Data, float _Step, const string& _Desc)
{
	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(100);

	char szID[255] = {};
	sprintf_s(szID, 255, "##DragVec4%d", g_ID++);

	if (ImGui::DragFloat4(szID, *_Data, _Step))
	{
		return true;
	}

	return false;
}


// Texture Parameter
#include "TreeUI.h"

bool ParamUI::InputTexture(Ptr<qTexture>& _CurTex, const string& _Desc
							, EditorUI* _Inst, DELEGATE_1 _MemFunc)
{
	Ptr<qTexture> CurTex = _CurTex;

	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(120);

	// 이미지
	ImVec2 uv_min = ImVec2(0.f, 0.f);
	ImVec2 uv_max = ImVec2(1.f, 1.f);

	ImTextureID TexID = nullptr;
	if (nullptr != CurTex)
		TexID = CurTex->GetSRV().Get();

	ImVec4 tint_col = ImVec4(1.f, 1.f, 1.f, 1.f);
	ImVec4 border_col = ImVec4(0.7f, 0.7f, 0.7f, 1.f);
	ImGui::Image(TexID, ImVec2(150, 150), uv_min, uv_max, tint_col, border_col);

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
				_CurTex = ((qTexture*)pAsset.Get());
			}
		}

		ImGui::EndDragDropTarget();
	}

	// Drag Drop 으로 원본 텍스쳐가 바뀐 경우
	if (CurTex != _CurTex)
		return true;

	// List Button
	if (nullptr == _Inst && nullptr == _MemFunc)
		return false;

	char szID[255] = {};
	sprintf_s(szID, 255, "##InputBtn%d", g_ID++);

	ImGui::SameLine();
	if (ImGui::Button(szID, ImVec2(18.f, 18.f)))
	{
		ListUI* pListUI = (ListUI*)qEditorMgr::GetInst()->FindEditorUI("List");
		pListUI->SetName("Texture");
		vector<string> vecTexNames;
		qAssetMgr::GetInst()->GetAssetNames(ASSET_TYPE::TEXTURE, vecTexNames);
		pListUI->AddList(vecTexNames);
		pListUI->AddDelegate(_Inst, (DELEGATE_1)_MemFunc);
		pListUI->SetActive(true);

		return true;
	}

	return false;

}

bool ParamUI::InputPrefab(Ptr<qPrefab>& _CurPrefab, const string& _Desc, EditorUI* _Inst, DELEGATE_1 _MemFunc)
{
	Ptr<qPrefab> CurPrefab = _CurPrefab;

	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(120);

	string PrefabName;

	if (CurPrefab.Get())
		PrefabName = string(CurPrefab->GetKey().begin(), CurPrefab->GetKey().end());

	char szID[255] = {};
	sprintf_s(szID, 255, "##PrefabKey%d", g_ID++);

	ImGui::SetNextItemWidth(150.f);
	ImGui::InputText(szID, (char*)PrefabName.c_str(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);

	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");
		if (payload)
		{
			TreeNode** ppNode = (TreeNode**)payload->Data;
			TreeNode* pNode = *ppNode;

			Ptr<qAsset> pAsset = (qAsset*)pNode->GetData();
			if (ASSET_TYPE::PREFAB == pAsset->GetAssetType())
			{
				_CurPrefab = ((qPrefab*)pAsset.Get());
			}
		}

		ImGui::EndDragDropTarget();
	}

	// DragDrop 으로 원본 텍스처가 바뀐 경우
	if (CurPrefab != _CurPrefab)
		return true;

	// List Button
	if (nullptr == _Inst && nullptr == _MemFunc)
		return false;

	sprintf_s(szID, 255, "##InputBtn%d", g_ID++);

	ImGui::SameLine();
	if (ImGui::Button(szID, ImVec2(18.f, 18.f)))
	{
		ListUI* pListUI = (ListUI*)qEditorMgr::GetInst()->FindEditorUI("List");
		pListUI->SetName("Prefab");
		vector<string> vecPrefabName;
		qAssetMgr::GetInst()->GetAssetNames(ASSET_TYPE::PREFAB, vecPrefabName);
		pListUI->AddList(vecPrefabName);
		pListUI->AddDelegate(_Inst, (DELEGATE_1)_MemFunc);
		pListUI->SetActive(true);

		return true;
	}

	return false;
}
