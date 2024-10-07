#include "pch.h"
#include "MeshRenderUI.h"

#include <Engine/qAssetMgr.h>
#include <Engine/qMeshRender.h>
#include <Engine/qMesh.h>
#include <Engine/qMaterial.h>

#include "qEditorMgr.h"
#include "ListUI.h"
#include "TreeUI.h"

MeshRenderUI::MeshRenderUI()
	: ComponentUI(COMPONENT_TYPE::MESHRENDER)
{

}

MeshRenderUI::~MeshRenderUI()
{
}



void MeshRenderUI::Update()
{
	Title();

	qMeshRender* pMeshRender = GetTargetObject()->MeshRender();

	// 메쉬 정보
	Ptr<qMesh> pMesh = pMeshRender->GetMesh();

	// Mesh가 nullptr일때는 이름을 받아오지 않도록 예외처리
	string MeshName;
	if(pMesh.Get())
		MeshName = string(pMesh->GetKey().begin(), pMesh->GetKey().end());
	
	ImGui::Text("Mesh");
	ImGui::SameLine(100);
	ImGui::SetNextItemWidth(150.f);
	ImGui::InputText("##MeshKey", (char*)MeshName.c_str(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);
	
	// Drag n Drop 시 PayLoad 설정
	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");
		if (payload)
		{
			TreeNode** ppNode = (TreeNode**)payload->Data;
			TreeNode* pNode = *ppNode;

			Ptr<qAsset> pAsset = (qAsset*)pNode->GetData();
			if (ASSET_TYPE::MESH == pAsset->GetAssetType())
			{
				pMeshRender->SetMesh((qMesh*)pAsset.Get());
			}
		}

		ImGui::EndDragDropTarget();
	}

	
	
	ImGui::SameLine();
	if (ImGui::Button("##MeshBtn", ImVec2(18.f, 18.f)))
	{
		ListUI* pListUI = (ListUI*)qEditorMgr::GetInst()->FindEditorUI("List");
		pListUI->SetName("Mesh");
		vector<string> vecMeshNames;
		qAssetMgr::GetInst()->GetAssetNames(ASSET_TYPE::MESH, vecMeshNames);
		pListUI->AddList(vecMeshNames);
		pListUI->AddDelegate(this, (DELEGATE_1)&MeshRenderUI::SelectMesh);
		pListUI->SetActive(true);
	}



	// 머티리얼 정보
	Ptr<qMaterial> pMtrl = pMeshRender->GetMaterial();
	
	// Mtrl 이 있을때, Name에 받아올수있도록 예외처리
	string MtrlName;
	if(pMtrl.Get())
		MtrlName = string(pMtrl->GetKey().begin(), pMtrl->GetKey().end());


	// ===========
	string strName = MtrlName;
	
	// NameOnly
	if (IsShowNameOnly())
	{
		path Path = MtrlName;
		strName = Path.stem().string();
	}
	
	// ===========

	ImGui::Text("Material");
	ImGui::SameLine(100);
	ImGui::SetNextItemWidth(150.f);
	//ImGui::InputText("##MaterialKey", (char*)MtrlName.c_str(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);
	ImGui::InputText("##MaterialKey", (char*)strName.c_str(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);

	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");
		if (payload)
		{
			TreeNode** ppNode = (TreeNode**)payload->Data;
			TreeNode* pNode = *ppNode;

			Ptr<qAsset> pAsset = (qAsset*)pNode->GetData();
			if (ASSET_TYPE::MATERIAL == pAsset->GetAssetType())
			{
				pMeshRender->SetMaterial((qMaterial*)pAsset.Get());
			}
		}

		ImGui::EndDragDropTarget();
	}


	ImGui::SameLine();
	if (ImGui::Button("##MtrlBtn", ImVec2(18.f, 18.f)))
	{
		ListUI* pListUI = (ListUI*)qEditorMgr::GetInst()->FindEditorUI("List");
		pListUI->SetName("Material");
		vector<string> vecMtrlNames;
		qAssetMgr::GetInst()->GetAssetNames(ASSET_TYPE::MATERIAL, vecMtrlNames);
		pListUI->AddList(vecMtrlNames);
		pListUI->AddDelegate(this, (DELEGATE_1)&MeshRenderUI::SelectMaterial);
		pListUI->SetActive(true);
	}
}


void MeshRenderUI::SelectMesh(DWORD_PTR _ListUI)
{
	qMeshRender* pMeshRender = GetTargetObject()->MeshRender();

	ListUI* pListUI = (ListUI*)_ListUI;
	string strName = pListUI->GetSelectName();

	if ("None" == strName)
	{
		pMeshRender->SetMesh(nullptr);
		return;
	}

	wstring strAssetName = wstring(strName.begin(), strName.end());

	Ptr<qMesh> pMesh = qAssetMgr::GetInst()->FindAsset<qMesh>(strAssetName);

	assert(pMesh.Get());

	pMeshRender->SetMesh(pMesh);
}

void MeshRenderUI::SelectMaterial(DWORD_PTR _ListUI)
{
	qMeshRender* pMeshRender = GetTargetObject()->MeshRender();

	ListUI* pListUI = (ListUI*)_ListUI;
	string strName = pListUI->GetSelectName();

	if ("None" == strName)
	{
		pMeshRender->SetMaterial(nullptr);
		return;
	}

	wstring strAssetName = wstring(strName.begin(), strName.end());

	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(strAssetName);

	assert(pMtrl.Get());

	pMeshRender->SetMaterial(pMtrl);
}