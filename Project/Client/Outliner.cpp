#include "pch.h"
#include "Outliner.h"

#include "TreeUI.h"
#include "Inspector.h"
#include "qEditorMgr.h"

#include <Engine/qLevelMgr.h>
#include <Engine/qLevel.h>
#include <Engine/qLayer.h>
#include <Engine/qGameObject.h>

Outliner::Outliner()
{
	m_Tree = new TreeUI;
	m_Tree->SetName("OutlinerTree");
	AddChild(m_Tree);

	// 트리 옵션 
	// 루트 보이지 않기
	m_Tree->ShowRoot(false);

	// Drag, Drop을 사용하겠다
	m_Tree->UseDrag(true);
	m_Tree->UseDrop(true);

	// Clicked Delegate 등록
	m_Tree->AddClickedDelegate(this, (DELEGATE_1)&Outliner::GameObjectClicked);

	// Self DragDrop Delegate 등록
	m_Tree->AddDragDropDelegate(this, (DELEGATE_2)&Outliner::GameObjectAddChild);

	// 외부 드랍 Delegate 등록
	m_Tree->AddDropDelegate(this, (DELEGATE_2)&Outliner::DroppedFromOuter);
	m_Tree->SetDropPayLoadName("ContentTree");


	// Asset 상태를 Content 의 TreeUI 에 반영
	RenewLevel();
}

Outliner::~Outliner()
{
}

void Outliner::Update()
{
	if (qLevelMgr::GetInst()->IsLevelChanged())
		RenewLevel();
}

void Outliner::RenewLevel()
{
	// 모든 내용 삭제
	m_Tree->Clear();

	// 루트 노드 생성
	TreeNode* pRootNode = m_Tree->AddNode(nullptr, "Root", 0);

	qLevel* pLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	if (nullptr == pLevel)
		return;

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		qLayer* pLayer = pLevel->GetLayer(i);
		const vector<qGameObject*>& vecObjects = pLayer->GetParentObjects();

		for (size_t i = 0; i < vecObjects.size(); ++i)
		{
			AddGameObject(pRootNode, vecObjects[i]);
		}
	}
}

void Outliner::AddGameObject(TreeNode* pNode, qGameObject* _Object)
{
	string ObjectName = string(_Object->GetName().begin(), _Object->GetName().end());

	TreeNode* pObjectNode = m_Tree->AddNode(pNode, ObjectName.c_str(), (DWORD_PTR)_Object);

	const vector<qGameObject*>& vecChild = _Object->GetChildren();

	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		AddGameObject(pObjectNode, vecChild[i]);
	}
}

void Outliner::GameObjectAddChild(DWORD_PTR _Param1, DWORD_PTR _Param2)
{
	TreeNode* pDragNode = (TreeNode*)_Param1;
	TreeNode* pDropNode = (TreeNode*)_Param2;

	qGameObject* pDragObject = ((qGameObject*)pDragNode->GetData());
	qGameObject* pDropObject = nullptr;

	// Drag 오브젝트를 Drop 오브젝트의 자식으로 넣어 준다.
	if (pDropNode)
	{
		pDropObject = ((qGameObject*)pDropNode->GetData());

		// 자식으로 들어갈 오브젝트가 부모(조상) 중 하나였다면 무시한다.
		if (pDropObject->IsAncestor(pDragObject))
			return;

		pDropObject->AddChild(pDragObject);
	}

	// Drop 목적지가 없는 경우 (공백에다가 드래그했을 경우)에는 Drag한 오브젝트를 최상위 부모로 넣어준다.
	else
	{
		// 그래도 부모를 끌었을때는 그냥 아무일도 일어나지않게 한다.
		if (!pDragObject->GetParent())
			return;

		// 부모 오브젝트랑 연결을 끊고
		pDragObject->DeregisterChild();

		// 본인 소속 레이어에 최상위 부모로써 등록한다.
		qLevelMgr::GetInst()->GetCurrentLevel()->RegisterAsParent(pDragObject->GetLayerIdx(), pDragObject);
	}
}

void Outliner::DroppedFromOuter(DWORD_PTR _OuterData, DWORD_PTR _DropNode)
{
	TreeNode* ContentNode = *((TreeNode**)_OuterData);
	TreeNode* DropNode = (TreeNode*)_DropNode;
}


void Outliner::GameObjectClicked(DWORD_PTR _Param)
{
	TreeNode* pNode = (TreeNode*)_Param;

	qGameObject* pObject = (qGameObject*)pNode->GetData();

	Inspector* pInspector = (Inspector*)qEditorMgr::GetInst()->FindEditorUI("Inspector");
	pInspector->SetTargetObject(pObject);
	//ImGui::SetWindowFocus(nullptr);
}


