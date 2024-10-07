#include "pch.h"
#include "qLevel_loading1.h"

#include <Engine/qAssetMgr.h>
#include <Engine/qAsset.h>
#include <Engine/assets.h>

#include <Engine/qFSM.h>
#include <Engine/qState.h>

#include <Engine/qCollisionMgr.h>
#include <Engine/qCollider2D.h>
#include <Engine/qLevelMgr.h>
#include <Engine/qTaskMgr.h>

#include <Engine/qLevel.h>
#include <Engine/qLayer.h>
#include <Engine/qGameObject.h>
#include <Engine/components.h>

#include <States/qLoading1State.h>

#include <Scripts/qCameraMoveScript.h>

void qLevel_loading1::CreateLoading1()
{
	// Material
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	Ptr<qMaterial> pAlphaBlendMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DAlphaBlendMtrl");
	Ptr<qMaterial> pDebugShapeMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"DebugShapeMtrl");

	// Level
	qLevel* pLoading1 = new qLevel;

	qLevelMgr::GetInst()->InsertLevel(L"loading1", pLoading1);

	pLoading1->SetName(L"loading1");

	pLoading1->GetLayer(0)->SetName(L"Camera");
	pLoading1->GetLayer(1)->SetName(L"Light");
	pLoading1->GetLayer(2)->SetName(L"LoadingFlip");

	// Camera
	qGameObject* CameraObject = new qGameObject;
	CameraObject->SetName(L"MainCamera");
	CameraObject->AddComponent(new qCameraMoveScript);
	CameraObject->AddComponent(new qCamera);
	CameraObject->AddComponent(new qTransform);

	// 우선순위를 0 : Main Camera 로 설정
	CameraObject->Camera()->SetPriority(0);

	// 카메라 레이어 설정
	CameraObject->Camera()->SetLayerAll();
	CameraObject->Camera()->SetFar(100000.f);
	CameraObject->Camera()->SetScale(1.0f);
	CameraObject->Camera()->SetProjType(ORTHOGRAPHIC);		// 직교 투영

	pLoading1->AddObject(0, CameraObject);


	// 맵 전체 태양광
	qGameObject* pLight = new qGameObject;
	pLight->SetName(L"PointLightMap");
	pLight->AddComponent(new qTransform);
	pLight->AddComponent(new qLight2D);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLight->Light2D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	pLight->Light2D()->SetRadius(10000.f);

	pLoading1->AddObject(1, pLight);


	// 로딩씬 Flipbook
	qGameObject* pLoadingFlip1 = new qGameObject;
	pLoadingFlip1->SetName(L"LoadingFlip1");

	pLoadingFlip1->AddComponent(new qTransform);
	pLoadingFlip1->Transform()->SetRelativePos(0.f, 0.f, 10.f);
	pLoadingFlip1->Transform()->SetRelativeScale(270.f, 350.f, 1.f);

	pLoadingFlip1->AddComponent(new qMeshRender);
	pLoadingFlip1->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pLoadingFlip1->MeshRender()->SetMaterial(pMtrl);

	pLoadingFlip1->AddComponent(new qFlipBookComponent);

	Ptr<qFlipBook> pLoadingFlipbook = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\loading.flip");
	pLoadingFlip1->FlipBookComponent()->AddFlipBook(1, pLoadingFlipbook);

	pLoadingFlip1->AddComponent(new qFSM);
	pLoadingFlip1->FSM()->AddState(L"loadingstate", new qLoading1State);

	pLoadingFlip1->FSM()->ChangeState(L"loadingstate");

	pLoading1->AddObject(2, pLoadingFlip1);
}
