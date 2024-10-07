#include "pch.h"

#include "qEditorMgr.h"
#include "qGameObjectEx.h"
#include <Engine/components.h>

#include "qEditorCameraScript.h"
#include <Engine/qRenderMgr.h>




void qEditorMgr::CreateEditorObject()
{
	// 에디터용 카메라 오브젝트 생성
	qGameObject* pEditorCamera = new qGameObjectEx;
	pEditorCamera->SetName(L"EditorCamera");
	pEditorCamera->AddComponent(new qTransform);
	pEditorCamera->AddComponent(new qCamera);
	pEditorCamera->AddComponent(new qEditorCameraScript);

	pEditorCamera->Camera()->SetLayerAll();
	pEditorCamera->Camera()->SetLayer(31, false);
	pEditorCamera->Camera()->SetFar(100000.f);
	pEditorCamera->Camera()->SetProjType(ORTHOGRAPHIC);

	m_vecEditorObject.push_back(pEditorCamera);

	// Editor 용 카메라로서 렌더매니저에 등록
	qRenderMgr::GetInst()->RegisterEditorCamera(pEditorCamera->Camera());
}