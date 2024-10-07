#include "pch.h"
#include "qLevel_title.h"


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

#include <Scripts/qPlayerScript.h>
#include <Scripts/qBookScript_Left.h>
#include <Scripts/qMissileScript.h>
#include <Scripts/qCameraMoveScript.h>
#include <Scripts/qPlatformScript.h>
#include <Scripts/qPortalScript.h>
#include <Scripts/qDoorScript.h>
#include <Scripts/qPostScript.h>
#include <Scripts/qCollectScript.h>

#include <Engine/qSetColorCS.h>
#include <Engine/qStructuredBuffer.h>

// ========================                    
//      Player State                         * INDEX *
// ========================

#include <States/qStateMgr.h>
#include <States/qPlayerIdleState.h>			// 0
#include <States/qPlayerWaitState.h>			// 1
#include <States/qPlayerRunState.h>				// 2
#include <States/qPlayerIdleToRunState.h>		// 3
#include <States/qPlayerRunToIdleState.h>		// 4
#include <States/qPlayerIdleUTurnState.h>		// 5
#include <States/qPlayerRunUTurnState.h>		// 6
#include <States/qPlayerJumpState.h>			// 7
#include <States/qPlayerFallingState.h>			// 8
#include <States/qPlayerLandingState.h>			// 9
#include <States/qPlayerDashState.h>			// 10
												// 11

#include <States/qPlayerCombo1State.h>			// 13
#include <States/qPlayerCombo2State.h>			// 14
#include <States/qPlayerCombo3State.h>			// 15
#include <States/qPlayerCombo4State.h>			// 16
#include <States/qPlayerBookShootState.h>		// 17

#include <States/qPlayerCrashState.h>			// 19
#include <States/qPlayerRangeState.h>			// 20
#include <States/qPlayerKrushState.h>			// 21
#include <States/qPlayerTeleportState.h>		// 22
#include <States/qPlayerTeleportFinishState.h>	// 23
#include <States/qPlayerBumpState.h>			// 24
#include <States/qPlayerNullState.h>			// 25


// ========================                    
//      Transfer State                         * INDEX *
// ========================


#include <States/qDoorStayState.h>				// 1
#include <States/qDoorOpenState.h>				// 2
#include <States/qDoorCloseState.h>				// 3

#include <States/qPostCloseState.h>				// 4
#include <States/qPostOpenState.h>				// 5


#include "qLevelSaveLoad.h"

void qLevel_title::CreateTitle()
{
	// Sound
	Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\background\\title.wav", L"sound\\background\\title.wav");
	pSound->Play(0, 0.5, true);




	// Material
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	Ptr<qMaterial> pAlphaBlendMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DAlphaBlendMtrl");
	Ptr<qMaterial> pDebugShapeMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"DebugShapeMtrl");

	Ptr<qMaterial> pMtrl2 = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"material\\titleBack.mtrl");
	Ptr<qMaterial> pCollectMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"material\\collect.mtrl");

	// Level
	qLevel* pTitle = new qLevel;

	qLevelMgr::GetInst()->InsertLevel(L"title", pTitle);

	pTitle->SetName(L"title");

	pTitle->GetLayer(0)->SetName(L"Camera");
	pTitle->GetLayer(1)->SetName(L"Background");
	pTitle->GetLayer(2)->SetName(L"Collect");
	pTitle->GetLayer(3)->SetName(L"Smoke");
	pTitle->GetLayer(4)->SetName(L"Post");


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

	pTitle->AddObject(0, CameraObject);


	// 배경
	qGameObject* pBackground = new qGameObject;
	pBackground->SetName(L"BGtitle");

	pBackground->AddComponent(new qTransform);
	pBackground->Transform()->SetRelativePos(0.f, 0.f, 50.f);
	pBackground->Transform()->SetRelativeScale(1600.f, 900.f, 1.f);

	pBackground->AddComponent(new qMeshRender);
	pBackground->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pBackground->MeshRender()->SetMaterial(pMtrl2);

	pTitle->AddObject(1, pBackground);


	// 맵 전체 태양광
	qGameObject* pLight = new qGameObject;
	pLight->SetName(L"PointLightMap");
	pLight->AddComponent(new qTransform);
	pLight->AddComponent(new qLight2D);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLight->Light2D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	pLight->Light2D()->SetRadius(10000.f);

	pTitle->AddObject(0, pLight);


	//qGameObject* pLightCollect = new qGameObject;
	//pLightCollect->SetName(L"PointLightMap");
	//pLightCollect->AddComponent(new qTransform);
	//pLightCollect->AddComponent(new qLight2D);
	//
	//pLightCollect->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	//pLightCollect->Light2D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	//pLightCollect->Light2D()->SetRadius(10.f);
	//
	//pTitle->AddObject(0, pLightCollect);



	// Monster Object
	//qGameObject* pMonster = new qGameObject;
	//pMonster->SetName(L"Monster");
	//
	//pMonster->AddComponent(new qTransform);
	//pMonster->AddComponent(new qCollider2D);
	//
	//pMonster->Transform()->SetRelativePos(-0.f, -0.f, 9.f);
	//pMonster->Transform()->SetRelativeScale(170.f, 140.f, 1.f);
	//
	//pMonster->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	//pMonster->Collider2D()->SetScale(Vec3(1.2f, 1.2f, 1.f));
	//
	//pMonster->AddComponent(new qMeshRender);
	//Ptr<qMaterial> pEffectMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"EffectMtrl");
	//pMonster->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	//pMonster->MeshRender()->SetMaterial(pEffectMtrl);
	//pMonster->MeshRender()->GetMaterial()->SetScalarParam(VEC4_0, Vec4(2.f, 10.f, 4.f, 1.f));
	//pMonster->MeshRender()->GetMaterial()->SetTexParam(TEX_0, qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\fire_11.png"));
	//
	//pTitle->AddObject(5, pMonster);


	// collect
	qGameObject* pCollect = new qGameObject;
	pCollect->SetName(L"collect");
	pCollect->AddComponent(new qCollectScript);
	pCollect->AddComponent(new qTransform);
	pCollect->Transform()->SetRelativePos(-732.f, -87.f, 30.f);
	pCollect->Transform()->SetRelativeScale(69.f, 70.f, 1.f);

	pCollect->AddComponent(new qMeshRender);
	pCollect->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pCollect->MeshRender()->SetMaterial(pAlphaBlendMtrl);

	pCollect->AddComponent(new qFlipBookComponent);

	Ptr<qFlipBook> pCollectFlip = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\collect.flip");
	pCollect->FlipBookComponent()->AddFlipBook(1, pCollectFlip);

	pCollect->FlipBookComponent()->Play(1, 10, false);

	pCollect->AddComponent(new qCollider2D);
	pCollect->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pCollect->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));

	pTitle->AddObject(2, pCollect);


	// smoke
	qGameObject* pSmoke = new qGameObject;
	pSmoke->SetName(L"smoke");

	pSmoke->AddComponent(new qTransform);
	pSmoke->Transform()->SetRelativePos(472.f, -84.f, 30.f);
	pSmoke->Transform()->SetRelativeScale(250.f, 200.f, 1.f);

	pSmoke->AddComponent(new qMeshRender);
	pSmoke->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pSmoke->MeshRender()->SetMaterial(pAlphaBlendMtrl);

	pSmoke->AddComponent(new qFlipBookComponent);

	Ptr<qFlipBook> pSmokeFlip = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\smoke.flip");
	pSmoke->FlipBookComponent()->AddFlipBook(2, pSmokeFlip);

	pSmoke->FlipBookComponent()->Play(2, 10, true);


	pTitle->AddObject(3, pSmoke);


	// Post Process (Level Change)
	qGameObject* pPostProcess = new qGameObject;
	pPostProcess->SetName(L"PostClose");

	pPostProcess->AddComponent(new qPostScript);
	pPostProcess->AddComponent(new qTransform);
	pPostProcess->Transform()->SetRelativePos(0.f, 0.f, 10.f);

	pPostProcess->AddComponent(new qMeshRender);
	pPostProcess->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pPostProcess->MeshRender()->SetMaterial(pAlphaBlendMtrl);

	pPostProcess->AddComponent(new qFlipBookComponent);

	Ptr<qFlipBook> pPostClose = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\chang.flip");
	pPostProcess->FlipBookComponent()->AddFlipBook(4, pPostClose);

	pPostProcess->AddComponent(new qFSM);
	pPostProcess->FSM()->AddState(L"PostClose", new qPostCloseState);

	pTitle->AddObject(9, pPostProcess);


	//ChangeLevel(pTitle, LEVEL_STATE::STOP);

}
