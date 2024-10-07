#include "pch.h"
#include "qLevel_loading.h"

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

#include <States/qLoadingState.h>

#include <Scripts/qCameraMoveScript.h>

void qLevel_loading::CreateLoading()
{
	// Sound

	// Material
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	Ptr<qMaterial> pAlphaBlendMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DAlphaBlendMtrl");
	Ptr<qMaterial> pDebugShapeMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"DebugShapeMtrl");


	// Level
	qLevel* pLoading = new qLevel;

	qLevelMgr::GetInst()->InsertLevel(L"loading", pLoading);

	pLoading->SetName(L"loading");

	pLoading->GetLayer(0)->SetName(L"Camera");
	pLoading->GetLayer(1)->SetName(L"Light");
	pLoading->GetLayer(2)->SetName(L"LoadingFlip");



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

	pLoading->AddObject(0, CameraObject);



	// 맵 전체 태양광
	qGameObject* pLight = new qGameObject;
	pLight->SetName(L"PointLightMap");
	pLight->AddComponent(new qTransform);
	pLight->AddComponent(new qLight2D);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLight->Light2D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	pLight->Light2D()->SetRadius(10000.f);

	pLoading->AddObject(1, pLight);


	// 로딩씬 Flipbook
	qGameObject* pLoadingFlip = new qGameObject;
	pLoadingFlip->SetName(L"LoadingFlip");

	pLoadingFlip->AddComponent(new qTransform);
	pLoadingFlip->Transform()->SetRelativePos(0.f, 0.f, 10.f);
	pLoadingFlip->Transform()->SetRelativeScale(270.f, 350.f, 1.f);

	pLoadingFlip->AddComponent(new qMeshRender);
	pLoadingFlip->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pLoadingFlip->MeshRender()->SetMaterial(pMtrl);

	pLoadingFlip->AddComponent(new qFlipBookComponent);

	Ptr<qFlipBook> pLoadingFlipbook = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\loading.flip");
	pLoadingFlip->FlipBookComponent()->AddFlipBook(1, pLoadingFlipbook);

	pLoadingFlip->AddComponent(new qFSM);
	pLoadingFlip->FSM()->AddState(L"loadingstate", new qLoadingState);

	pLoadingFlip->FSM()->ChangeState(L"loadingstate");

	pLoading->AddObject(2, pLoadingFlip);


}
