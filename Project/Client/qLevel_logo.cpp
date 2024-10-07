#include "pch.h"
#include "qLevel_logo.h"

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

#include <States/qLogoState.h>

#include <Scripts/qCameraMoveScript.h>

void qLevel_logo::CreateLogo()
{
	// sound
	Ptr<qSound> pSoundTitle = qAssetMgr::GetInst()->Load<qSound>(L"sound\\background\\title.wav", L"sound\\background\\title.wav");
	pSoundTitle->Stop();

	Ptr<qSound> pSoundstage1 = qAssetMgr::GetInst()->Load<qSound>(L"sound\\background\\stage1.wav", L"sound\\background\\stage1.wav");
	pSoundstage1->Stop();

	Ptr<qSound> pSoundstage2 = qAssetMgr::GetInst()->Load<qSound>(L"sound\\background\\stage2.wav", L"sound\\background\\stage2.wav");
	pSoundstage2->Stop();

	Ptr<qSound> pSoundPostOpen = qAssetMgr::GetInst()->Load<qSound>(L"sound\\transfer\\postopen.wav", L"sound\\transfer\\postopen.wav");
	pSoundPostOpen->Stop();

	Ptr<qSound> pSoundPostClose = qAssetMgr::GetInst()->Load<qSound>(L"sound\\transfer\\postclose.wav", L"sound\\transfer\\postclose.wav");
	pSoundPostClose->Stop();

	//Ptr<qSound> pSoundEleOpen = qAssetMgr::GetInst()->Load<qSound>(L"sound\\transfer\\eleopenup.wav", L"sound\\transfer\\eleopenup.wav");
	//pSoundEleOpen->Stop();
	//
	//Ptr<qSound> pSoundEleClose = qAssetMgr::GetInst()->Load<qSound>(L"sound\\transfer\\eleclosedown.wav", L"sound\\transfer\\eleclosedown.wav");
	//pSoundEleClose->Stop();


	// Material
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	Ptr<qMaterial> pAlphaBlendMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DAlphaBlendMtrl");
	Ptr<qMaterial> pDebugShapeMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"DebugShapeMtrl");


	// Level
	qLevel* pLogo = new qLevel;


	qLevelMgr::GetInst()->InsertLevel(L"logo", pLogo);

	pLogo->SetName(L"logo");

	pLogo->GetLayer(0)->SetName(L"Camera");
	pLogo->GetLayer(1)->SetName(L"Light");
	pLogo->GetLayer(2)->SetName(L"LogoFlip");


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

	pLogo->AddObject(0, CameraObject);


	// 맵 전체 태양광
	qGameObject* pLight = new qGameObject;
	pLight->SetName(L"PointLightMap");
	pLight->AddComponent(new qTransform);
	pLight->AddComponent(new qLight2D);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLight->Light2D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	pLight->Light2D()->SetRadius(10000.f);

	pLogo->AddObject(1, pLight);


	// 로고씬 FlipBook

	qGameObject* pLogoFlip = new qGameObject;
	pLogoFlip->SetName(L"LogoFlip");

	pLogoFlip->AddComponent(new qTransform);
	pLogoFlip->Transform()->SetRelativePos(0.f, 0.f, 10.f);
	pLogoFlip->Transform()->SetRelativeScale(462.f, 274.2f, 1.f);

	pLogoFlip->AddComponent(new qMeshRender);
	pLogoFlip->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pLogoFlip->MeshRender()->SetMaterial(pAlphaBlendMtrl);

	pLogoFlip->AddComponent(new qFlipBookComponent);

	Ptr<qFlipBook> pLogoFlipbook = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\logo3.flip");
	pLogoFlip->FlipBookComponent()->AddFlipBook(1, pLogoFlipbook);

	pLogoFlip->AddComponent(new qFSM);
	pLogoFlip->FSM()->AddState(L"logostate", new qLogoState);

	pLogoFlip->FSM()->ChangeState(L"logostate");

	pLogo->AddObject(2, pLogoFlip);


	ChangeLevel(pLogo, LEVEL_STATE::PLAY);
}
