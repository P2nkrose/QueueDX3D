#include "pch.h"
#include "qLevel_stage2.h"


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
#include <Scripts/qPlayerHUDScript.h>

// Monster Script
#include <Scripts/qSkeletonScript.h>
#include <Scripts/qDrownedScript.h>
#include <Scripts/qGhostScript.h>

#include <Scripts/qBookScript_Left.h>
#include <Scripts/qMissileScript.h>
#include <Scripts/qCameraMoveScript.h>
#include <Scripts/qPlatformScript.h>
#include <Scripts/qWallScript.h>
#include <Scripts/qPostScript.h>



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
#include <States/qPlayerElevatorOutState.h>		// 11
#include <States/qPlayerGetItemState.h>			// 12
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

#include <States/qPostCloseState.h>				// 4
#include <States/qPostOpenState.h>				// 5

#include <States/qElevatorStayState.h>			// 6
#include <States/qElevatorOpenState.h>			// 7
#include <States/qElevatorCloseState.h>			// 8

// ========================                    
//      Monster State                         * INDEX *
// ========================

#include <States/qSkeletonIdleState.h>			// 0
#include <States/qSkeletonAttackState.h>		// 1
#include <States/qSkeletonDeathState.h>			// 2

#include <States/qDrownedIdleState.h>			// 0
#include <States/qDrownedRunState.h>			// 1
#include <States/qDrownedUturnState.h>			// 2
#include <States/qDrownedAttackState.h>			// 3
#include <States/qDrownedHitState.h>			// 4
#include <States/qDrownedDeathState.h>			// 5

#include <States/qGhostIdleState.h>				// 0
#include <States/qGhostRunState.h>				// 1
#include <States/qGhostUturnState.h>			// 2
#include <States/qGhostAttackState.h>			// 3
#include <States/qGhostHitState.h>				// 4
#include <States/qGhostDeathState.h>			// 5


#include "qLevelSaveLoad.h"

void qLevel_stage2::CreateStage2()
{
	// Sound
	Ptr<qSound> pSound = qAssetMgr::GetInst()->Load<qSound>(L"sound\\background\\stage2.wav", L"sound\\background\\stage2.wav");
	pSound->Play(0, 0.5, true);

	// Material
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	Ptr<qMaterial> pAlphaBlendMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DAlphaBlendMtrl");
	Ptr<qMaterial> pDebugShapeMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"DebugShapeMtrl");

	Ptr<qMaterial> pMtrl2 = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"material\\stage2Back2.mtrl");

	Ptr<qMaterial> pUIMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DUIMtrl");
	Ptr<qTexture> pUI = qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\UI\\UI.png");
	pUIMtrl->SetTexParam(TEX_0, pUI);


	// Level
	qLevel* pStage2 = new qLevel;

	qLevelMgr::GetInst()->InsertLevel(L"stage2", pStage2);

	pStage2->SetName(L"stage2");

	pStage2->GetLayer(0)->SetName(L"Camera");
	pStage2->GetLayer(1)->SetName(L"Background");
	pStage2->GetLayer(2)->SetName(L"Platform");
	pStage2->GetLayer(3)->SetName(L"Player");
	pStage2->GetLayer(4)->SetName(L"PlayerSkill");
	pStage2->GetLayer(5)->SetName(L"Monster");
	pStage2->GetLayer(6)->SetName(L"MonsterSkill");
	pStage2->GetLayer(7)->SetName(L"Boss");
	pStage2->GetLayer(8)->SetName(L"BossSkill");
	pStage2->GetLayer(9)->SetName(L"Portal");
	pStage2->GetLayer(10)->SetName(L"Light");
	pStage2->GetLayer(11)->SetName(L"Wall");
	pStage2->GetLayer(12)->SetName(L"Effect");
	pStage2->GetLayer(13)->SetName(L"Clap");
	pStage2->GetLayer(14)->SetName(L"Item");
	pStage2->GetLayer(31)->SetName(L"UI");

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
	CameraObject->Camera()->SetLayer(31, false);
	CameraObject->Camera()->SetFar(100000.f);
	CameraObject->Camera()->SetScale(1.0f);
	CameraObject->Camera()->SetProjType(ORTHOGRAPHIC);		// 직교 투영

	pStage2->AddObject(0, CameraObject);


	// UI 카메라
	qGameObject* UICameraObject = new qGameObject;
	UICameraObject->SetName(L"UICamera");
	UICameraObject->AddComponent(new qCamera);
	UICameraObject->AddComponent(new qTransform);
	UICameraObject->Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));
	//UICameraObject->AddComponent(new qCameraMoveScript);

	UICameraObject->Camera()->SetPriority(1);

	UICameraObject->Camera()->SetLayer(31, true);
	UICameraObject->Camera()->SetFar(100000.f);
	UICameraObject->Camera()->SetScale(1.0f);
	UICameraObject->Camera()->SetProjType(ORTHOGRAPHIC);		// 직교 투영

	pStage2->AddObject(0, UICameraObject);
	


	// 광원 오브젝트
	qGameObject* pLightUI = new qGameObject;
	pLightUI->SetName(L"LightUI");
	pLightUI->AddComponent(new qTransform);
	pLightUI->AddComponent(new qLight2D);

	pLightUI->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLightUI->Light2D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	pLightUI->Light2D()->SetRadius(1000.f);


	// UI
	qGameObject* UI = new qGameObject;
	UI->SetName(L"UI");
	UI->AddChild(pLightUI);
	UI->AddComponent(new qTransform);
	UI->Transform()->SetRelativePos(0.f, -15.f, 10.f);
	UI->Transform()->SetRelativeScale(1600.f, 900.f, 1.f);


	UI->AddComponent(new qMeshRender);
	UI->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	UI->MeshRender()->SetMaterial(pUIMtrl);

	pStage2->AddObject(31, UI);


	// Player HUD
	Ptr<qMaterial> pHUDMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DHUDMtrl");
	Ptr<qTexture> pPlayerHUDUI = qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\UI\\playerHUD.png");
	pHUDMtrl->SetTexParam(TEX_0, pPlayerHUDUI);


	qGameObject* PlayerHUD = new qGameObject;
	PlayerHUD->SetName(L"PlayerHUD");
	PlayerHUD->AddComponent(new qTransform);
	PlayerHUD->Transform()->SetRelativePos(-427.f, 372.f, 1.f);
	PlayerHUD->Transform()->SetRelativeScale(413.f, 10.f, 1.f);

	PlayerHUD->AddComponent(new qPlayerHUDScript);
	PlayerHUD->AddComponent(new qMeshRender);
	PlayerHUD->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));

	PlayerHUD->MeshRender()->SetMaterial(pHUDMtrl);

	pStage2->AddObject(31, PlayerHUD);



	// 배경
	qGameObject* pBackground = new qGameObject;
	pBackground->SetName(L"BGstage2");

	pBackground->AddComponent(new qTransform);
	pBackground->Transform()->SetRelativePos(0.f, 0.f, 50.f);
	pBackground->Transform()->SetRelativeScale(11482.f, 1789.f, 1.f);

	pBackground->AddComponent(new qMeshRender);
	pBackground->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pBackground->MeshRender()->SetMaterial(pMtrl2);

	pStage2->AddObject(1, pBackground);


	// ============
	//   Platform
	// ============

	// Platform 1
	qGameObject* pPlatform1 = new qGameObject;
	pPlatform1->SetName(L"Platform");
	pPlatform1->AddComponent(new qPlatformScript);
	pPlatform1->AddComponent(new qTransform);
	pPlatform1->Transform()->SetRelativePos(-5028.f, -271.f, 10.f);
	pPlatform1->Transform()->SetRelativeScale(1427.f, 15.f, 1.f);
	pPlatform1->AddComponent(new qCollider2D);
	pPlatform1->Collider2D()->SetIndependentScale(false);
	pPlatform1->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform1->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform1);

	// Platform 2
	qGameObject* pPlatform2 = new qGameObject;
	pPlatform2->SetName(L"Platform");
	pPlatform2->AddComponent(new qPlatformScript);
	pPlatform2->AddComponent(new qTransform);
	pPlatform2->Transform()->SetRelativePos(-5092.f, -615.f, 10.f);
	pPlatform2->Transform()->SetRelativeScale(1302.f, 5.f, 1.f);
	pPlatform2->AddComponent(new qCollider2D);
	pPlatform2->Collider2D()->SetIndependentScale(false);
	pPlatform2->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform2->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform2);

	// Platform 3
	qGameObject* pPlatform3 = new qGameObject;
	pPlatform3->SetName(L"Platform");
	pPlatform3->AddComponent(new qPlatformScript);
	pPlatform3->AddComponent(new qTransform);
	pPlatform3->Transform()->SetRelativePos(-3920.f, -153.f, 10.f);
	pPlatform3->Transform()->SetRelativeScale(502.f, 5.f, 1.f);
	pPlatform3->AddComponent(new qCollider2D);
	pPlatform3->Collider2D()->SetIndependentScale(false);
	pPlatform3->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform3->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform3);

	// Platform 4
	qGameObject* pPlatform4 = new qGameObject;
	pPlatform4->SetName(L"Platform");
	pPlatform4->AddComponent(new qPlatformScript);
	pPlatform4->AddComponent(new qTransform);
	pPlatform4->Transform()->SetRelativePos(-4061.f, -667.f, 10.f);
	pPlatform4->Transform()->SetRelativeScale(770.f, 5.f, 1.f);
	pPlatform4->AddComponent(new qCollider2D);
	pPlatform4->Collider2D()->SetIndependentScale(false);
	pPlatform4->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform4->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform4);

	// Platform 5
	qGameObject* pPlatform5 = new qGameObject;
	pPlatform5->SetName(L"Platform");
	pPlatform5->AddComponent(new qPlatformScript);
	pPlatform5->AddComponent(new qTransform);
	pPlatform5->Transform()->SetRelativePos(-3385.f, -469.f, 10.f);
	pPlatform5->Transform()->SetRelativeScale(698.f, 5.f, 1.f);
	pPlatform5->AddComponent(new qCollider2D);
	pPlatform5->Collider2D()->SetIndependentScale(false);
	pPlatform5->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform5->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform5);

	// Platform 6
	qGameObject* pPlatform6 = new qGameObject;
	pPlatform6->SetName(L"Platform");
	pPlatform6->AddComponent(new qPlatformScript);
	pPlatform6->AddComponent(new qTransform);
	pPlatform6->Transform()->SetRelativePos(-2966.f, -153.f, 10.f);
	pPlatform6->Transform()->SetRelativeScale(501.f, 5.f, 1.f);
	pPlatform6->AddComponent(new qCollider2D);
	pPlatform6->Collider2D()->SetIndependentScale(false);
	pPlatform6->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform6->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform6);

	// Platform 7
	qGameObject* pPlatform7 = new qGameObject;
	pPlatform7->SetName(L"Platform");
	pPlatform7->AddComponent(new qPlatformScript);
	pPlatform7->AddComponent(new qTransform);
	pPlatform7->Transform()->SetRelativePos(-2266.f, 204.f, 10.f);
	pPlatform7->Transform()->SetRelativeScale(1224.f, 5.f, 1.f);
	pPlatform7->AddComponent(new qCollider2D);
	pPlatform7->Collider2D()->SetIndependentScale(false);
	pPlatform7->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform7->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform7);

	// Platform 8
	qGameObject* pPlatform8 = new qGameObject;
	pPlatform8->SetName(L"Platform");
	pPlatform8->AddComponent(new qPlatformScript);
	pPlatform8->AddComponent(new qTransform);
	pPlatform8->Transform()->SetRelativePos(-1870.f, -156.f, 10.f);
	pPlatform8->Transform()->SetRelativeScale(1427.f, 5.f, 1.f);
	pPlatform8->AddComponent(new qCollider2D);
	pPlatform8->Collider2D()->SetIndependentScale(false);
	pPlatform8->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform8->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform8);


	// Platform 9
	qGameObject* pPlatform9 = new qGameObject;
	pPlatform9->SetName(L"Platform");
	pPlatform9->AddComponent(new qPlatformScript);
	pPlatform9->AddComponent(new qTransform);
	pPlatform9->Transform()->SetRelativePos(-991.f, 64.f, 10.f);
	pPlatform9->Transform()->SetRelativeScale(633.f, 5.f, 1.f);
	pPlatform9->AddComponent(new qCollider2D);
	pPlatform9->Collider2D()->SetIndependentScale(false);
	pPlatform9->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform9->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform9);

	// Platform 10
	qGameObject* pPlatform10 = new qGameObject;
	pPlatform10->SetName(L"Platform");
	pPlatform10->AddComponent(new qPlatformScript);
	pPlatform10->AddComponent(new qTransform);
	pPlatform10->Transform()->SetRelativePos(-253.f, -70.f, 10.f);
	pPlatform10->Transform()->SetRelativeScale(566.f, 5.f, 1.f);
	pPlatform10->AddComponent(new qCollider2D);
	pPlatform10->Collider2D()->SetIndependentScale(false);
	pPlatform10->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform10->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform10);

	// Platform 11
	qGameObject* pPlatform11 = new qGameObject;
	pPlatform11->SetName(L"Platform");
	pPlatform11->AddComponent(new qPlatformScript);
	pPlatform11->AddComponent(new qTransform);
	pPlatform11->Transform()->SetRelativePos(-592.f, -434.f, 10.f);
	pPlatform11->Transform()->SetRelativeScale(884.f, 5.f, 1.f);
	pPlatform11->AddComponent(new qCollider2D);
	pPlatform11->Collider2D()->SetIndependentScale(false);
	pPlatform11->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform11->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform11);

	// Platform 12
	qGameObject* pPlatform12 = new qGameObject;
	pPlatform12->SetName(L"Platform");
	pPlatform12->AddComponent(new qPlatformScript);
	pPlatform12->AddComponent(new qTransform);
	pPlatform12->Transform()->SetRelativePos(70.f, -290.f, 10.f);
	pPlatform12->Transform()->SetRelativeScale(499.f, 5.f, 1.f);
	pPlatform12->AddComponent(new qCollider2D);
	pPlatform12->Collider2D()->SetIndependentScale(false);
	pPlatform12->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform12->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform12);

	// Platform 13
	qGameObject* pPlatform13 = new qGameObject;
	pPlatform13->SetName(L"Platform");
	pPlatform13->AddComponent(new qPlatformScript);
	pPlatform13->AddComponent(new qTransform);
	pPlatform13->Transform()->SetRelativePos(773.f, 32.f, 10.f);
	pPlatform13->Transform()->SetRelativeScale(1276.f, 5.f, 1.f);
	pPlatform13->AddComponent(new qCollider2D);
	pPlatform13->Collider2D()->SetIndependentScale(false);
	pPlatform13->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform13->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform13);

	// Platform 14
	qGameObject* pPlatform14 = new qGameObject;
	pPlatform14->SetName(L"Platform");
	pPlatform14->AddComponent(new qPlatformScript);
	pPlatform14->AddComponent(new qTransform);
	pPlatform14->Transform()->SetRelativePos(894.f, -292.f, 10.f);
	pPlatform14->Transform()->SetRelativeScale(861.f, 5.f, 1.f);
	pPlatform14->AddComponent(new qCollider2D);
	pPlatform14->Collider2D()->SetIndependentScale(false);
	pPlatform14->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform14->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform14);


	// Platform 15
	qGameObject* pPlatform15 = new qGameObject;
	pPlatform15->SetName(L"Platform");
	pPlatform15->AddComponent(new qPlatformScript);
	pPlatform15->AddComponent(new qTransform);
	pPlatform15->Transform()->SetRelativePos(1596.f, -504.f, 10.f);
	pPlatform15->Transform()->SetRelativeScale(557.f, 5.f, 1.f);
	pPlatform15->AddComponent(new qCollider2D);
	pPlatform15->Collider2D()->SetIndependentScale(false);
	pPlatform15->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform15->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform15);

	// Platform 16
	qGameObject* pPlatform16 = new qGameObject;
	pPlatform16->SetName(L"Platform");
	pPlatform16->AddComponent(new qPlatformScript);
	pPlatform16->AddComponent(new qTransform);
	pPlatform16->Transform()->SetRelativePos(2982.f, -10.f, 10.f);
	pPlatform16->Transform()->SetRelativeScale(605.f, 5.f, 1.f);
	pPlatform16->AddComponent(new qCollider2D);
	pPlatform16->Collider2D()->SetIndependentScale(false);
	pPlatform16->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform16->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform16);

	// Platform 17
	qGameObject* pPlatform17 = new qGameObject;
	pPlatform17->SetName(L"Platform");
	pPlatform17->AddComponent(new qPlatformScript);
	pPlatform17->AddComponent(new qTransform);
	pPlatform17->Transform()->SetRelativePos(3848.f, -10.f, 10.f);
	pPlatform17->Transform()->SetRelativeScale(605.f, 5.f, 1.f);
	pPlatform17->AddComponent(new qCollider2D);
	pPlatform17->Collider2D()->SetIndependentScale(false);
	pPlatform17->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform17->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform17);

	// Platform 18
	qGameObject* pPlatform18 = new qGameObject;
	pPlatform18->SetName(L"Platform");
	pPlatform18->AddComponent(new qPlatformScript);
	pPlatform18->AddComponent(new qTransform);
	pPlatform18->Transform()->SetRelativePos(3810.f, -298.f, 10.f);
	pPlatform18->Transform()->SetRelativeScale(3886.f, 5.f, 1.f);
	pPlatform18->AddComponent(new qCollider2D);
	pPlatform18->Collider2D()->SetIndependentScale(false);
	pPlatform18->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform18->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform18);



	// ============
	//     Wall
	// ============

	// Wall 1
	qGameObject* pWall1 = new qGameObject;
	pWall1->SetName(L"Wall");
	pWall1->AddComponent(new qWallScript);
	pWall1->AddComponent(new qTransform);
	pWall1->Transform()->SetRelativePos(-4448.f, -649.f, 10.f);
	pWall1->Transform()->SetRelativeScale(15.f, 45.f, 1.f);
	pWall1->AddComponent(new qCollider2D);
	pWall1->Collider2D()->SetIndependentScale(false);
	pWall1->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pWall1->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(11, pWall1);

	// Wall 2
	qGameObject* pWall2 = new qGameObject;
	pWall2->SetName(L"Wall");
	pWall2->AddComponent(new qWallScript);
	pWall2->AddComponent(new qTransform);
	pWall2->Transform()->SetRelativePos(-3687.f, -595.f, 10.f);
	pWall2->Transform()->SetRelativeScale(15.f, 154.f, 1.f);
	pWall2->AddComponent(new qCollider2D);
	pWall2->Collider2D()->SetIndependentScale(false);
	pWall2->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pWall2->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(11, pWall2);

	// Wall 3
	qGameObject* pWall3 = new qGameObject;
	pWall3->SetName(L"Wall");
	pWall3->AddComponent(new qWallScript);
	pWall3->AddComponent(new qTransform);
	pWall3->Transform()->SetRelativePos(-3029.f, -351.f, 10.f);
	pWall3->Transform()->SetRelativeScale(15.f, 249.f, 1.f);
	pWall3->AddComponent(new qCollider2D);
	pWall3->Collider2D()->SetIndependentScale(false);
	pWall3->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pWall3->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(11, pWall3);

	// Wall 4
	qGameObject* pWall4 = new qGameObject;
	pWall4->SetName(L"Wall");
	pWall4->AddComponent(new qWallScript);
	pWall4->AddComponent(new qTransform);
	pWall4->Transform()->SetRelativePos(-2710.f, 3.f, 10.f);
	pWall4->Transform()->SetRelativeScale(15.f, 325.f, 1.f);
	pWall4->AddComponent(new qCollider2D);
	pWall4->Collider2D()->SetIndependentScale(false);
	pWall4->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pWall4->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(11, pWall4);

	// Wall 5
	qGameObject* pWall5 = new qGameObject;
	pWall5->SetName(L"Wall");
	pWall5->AddComponent(new qWallScript);
	pWall5->AddComponent(new qTransform);
	pWall5->Transform()->SetRelativePos(-2588.f, 3.f, 10.f);
	pWall5->Transform()->SetRelativeScale(15.f, 325.f, 1.f);
	pWall5->AddComponent(new qCollider2D);
	pWall5->Collider2D()->SetIndependentScale(false);
	pWall5->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pWall5->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(11, pWall5);

	// Wall 6
	qGameObject* pWall6 = new qGameObject;
	pWall6->SetName(L"Wall");
	pWall6->AddComponent(new qWallScript);
	pWall6->AddComponent(new qTransform);
	pWall6->Transform()->SetRelativePos(-1150.f, -65.f, 10.f);
	pWall6->Transform()->SetRelativeScale(15.f, 199.f, 1.f);
	pWall6->AddComponent(new qCollider2D);
	pWall6->Collider2D()->SetIndependentScale(false);
	pWall6->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pWall6->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(11, pWall6);

	// Wall 7
	qGameObject* pWall7 = new qGameObject;
	pWall7->SetName(L"Wall");
	pWall7->AddComponent(new qWallScript);
	pWall7->AddComponent(new qTransform);
	pWall7->Transform()->SetRelativePos(-1044.f, -203.f, 10.f);
	pWall7->Transform()->SetRelativeScale(15.f, 478.f, 1.f);
	pWall7->AddComponent(new qCollider2D);
	pWall7->Collider2D()->SetIndependentScale(false);
	pWall7->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pWall7->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(11, pWall7);

	// Wall 8
	qGameObject* pWall8 = new qGameObject;
	pWall8->SetName(L"Wall");
	pWall8->AddComponent(new qWallScript);
	pWall8->AddComponent(new qTransform);
	pWall8->Transform()->SetRelativePos(328.f, -155.f, 10.f);
	pWall8->Transform()->SetRelativeScale(15.f, 280.f, 1.f);
	pWall8->AddComponent(new qCollider2D);
	pWall8->Collider2D()->SetIndependentScale(false);
	pWall8->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pWall8->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(11, pWall8);

	// Wall 9
	qGameObject* pWall9 = new qGameObject;
	pWall9->SetName(L"Wall");
	pWall9->AddComponent(new qWallScript);
	pWall9->AddComponent(new qTransform);
	pWall9->Transform()->SetRelativePos(455.f, -155.f, 10.f);
	pWall9->Transform()->SetRelativeScale(15.f, 280.f, 1.f);
	pWall9->AddComponent(new qCollider2D);
	pWall9->Collider2D()->SetIndependentScale(false);
	pWall9->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pWall9->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(11, pWall9);

	// Wall 10
	qGameObject* pWall10 = new qGameObject;
	pWall10->SetName(L"Wall");
	pWall10->AddComponent(new qWallScript);
	pWall10->AddComponent(new qTransform);
	pWall10->Transform()->SetRelativePos(1308.f, -417.f, 10.f);
	pWall10->Transform()->SetRelativeScale(15.f, 189.f, 1.f);
	pWall10->AddComponent(new qCollider2D);
	pWall10->Collider2D()->SetIndependentScale(false);
	pWall10->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pWall10->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(11, pWall10);

	// Wall 11
	qGameObject* pWall11 = new qGameObject;
	pWall11->SetName(L"Wall");
	pWall11->AddComponent(new qWallScript);
	pWall11->AddComponent(new qTransform);
	pWall11->Transform()->SetRelativePos(1883.f, -417.f, 10.f);
	pWall11->Transform()->SetRelativeScale(15.f, 189.f, 1.f);
	pWall11->AddComponent(new qCollider2D);
	pWall11->Collider2D()->SetIndependentScale(false);
	pWall11->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pWall11->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(11, pWall11);


	// ==================
	//    광원 오브젝트
	// ==================

	// 광원오브젝트 - 맵 전체 태양광
	//qGameObject* pLight = new qGameObject;
	//pLight->SetName(L"PointLightMap");
	//pLight->AddComponent(new qTransform);
	//pLight->AddComponent(new qLight2D);
	//
	//pLight->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	//pLight->Light2D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	//pLight->Light2D()->SetRadius(500.f);
	//
	//pStage2->AddObject(0, pLight);

	// 광원 오브젝트 - 엘리베이터용
	//qGameObject* pLightEle1 = new qGameObject;
	//pLightEle1->SetName(L"PointLightEle");
	//pLightEle1->AddComponent(new qTransform);
	//pLightEle1->AddComponent(new qLight2D);

	//pLightEle1->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	//pLightEle1->Light2D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	//pLightEle1->Light2D()->SetRadius(100.f);

	// 광원 오브젝트 - 캐릭터용
	qGameObject* pLightPlayer = new qGameObject;
	pLightPlayer->SetName(L"PointLightPlayer");
	pLightPlayer->AddComponent(new qTransform);
	pLightPlayer->AddComponent(new qLight2D);

	pLightPlayer->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	pLightPlayer->Light2D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	pLightPlayer->Light2D()->SetRadius(5000.f);




	// =============
	//   TRANSFER
	// =============

	// Elevator 1
	qGameObject* pElevator1 = new qGameObject;
	pElevator1->SetName(L"pElevator1");
	//pElevator1->AddChild(pLightEle1);

	pElevator1->AddComponent(new qTransform);
	pElevator1->Transform()->SetRelativePos(-4924.f, -137.f, 11.f);
	pElevator1->Transform()->SetRelativeScale(550.f, 400.f, 1.f);

	pElevator1->AddComponent(new qMeshRender);
	pElevator1->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pElevator1->MeshRender()->SetMaterial(pAlphaBlendMtrl);

	pElevator1->AddComponent(new qFlipBookComponent);

	Ptr<qFlipBook> pElevatorStay = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\elevatorstay.flip");
	pElevator1->FlipBookComponent()->AddFlipBook(6, pElevatorStay);
	
	Ptr<qFlipBook> pElevatorOpen = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\elevatoropen.flip");
	pElevator1->FlipBookComponent()->AddFlipBook(7, pElevatorOpen);

	pElevator1->FlipBookComponent()->Play(7, 15, false);

	pElevator1->AddComponent(new qFSM);

	pElevator1->FSM()->AddState(L"ElevatorStay", new qElevatorStayState);		// 6
	pElevator1->FSM()->AddState(L"ElevatorOpen", new qElevatorOpenState);		// 7
	pElevator1->FSM()->AddState(L"ElevatorClose", new qElevatorCloseState);		// 8


	pElevator1->FSM()->ChangeState(L"ElevatorOpen");

	pStage2->AddObject(9, pElevator1);


	// Elevator 2
	qGameObject* pElevator2 = new qGameObject;
	pElevator2->SetName(L"Elevator2");
	//pElevator1->AddChild(pLightEle1);

	pElevator2->AddComponent(new qTransform);
	pElevator2->Transform()->SetRelativePos(5190.f, -157.f, 30.f);
	pElevator2->Transform()->SetRelativeScale(550.f, 400.f, 1.f);

	pElevator2->AddComponent(new qMeshRender);
	pElevator2->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pElevator2->MeshRender()->SetMaterial(pAlphaBlendMtrl);

	pElevator2->AddComponent(new qFlipBookComponent);

	//Ptr<qFlipBook> pElevatorStay = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\elevatorstay.flip");
	pElevator2->FlipBookComponent()->AddFlipBook(6, pElevatorStay);

	//Ptr<qFlipBook> pElevatorOpen = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\elevatoropen.flip");
	pElevator2->FlipBookComponent()->AddFlipBook(7, pElevatorOpen);

	Ptr<qFlipBook> pElevatorClose = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\elevatorclose.flip");
	pElevator2->FlipBookComponent()->AddFlipBook(8, pElevatorClose);

	pElevator2->FlipBookComponent()->Play(6, 15, false);


	pElevator2->AddComponent(new qCollider2D);
	pElevator2->Collider2D()->SetIndependentScale(false);
	pElevator2->Collider2D()->SetScale(Vec3(0.17f, 0.7f, 1.f));
	pElevator2->Collider2D()->SetOffset(Vec3(0.03f, 0.f, 0.f));


	pElevator2->AddComponent(new qFSM);

	pElevator2->FSM()->AddState(L"ElevatorStay", new qElevatorStayState);		// 6
	pElevator2->FSM()->AddState(L"ElevatorOpen", new qElevatorOpenState);		// 7
	pElevator2->FSM()->AddState(L"ElevatorClose", new qElevatorCloseState);		// 8


	pElevator2->FSM()->ChangeState(L"ElevatorStay");

	pStage2->AddObject(9, pElevator2);






	// Post Process (Level Change)
	qGameObject* pPostProcess1 = new qGameObject;
	pPostProcess1->SetName(L"PostOpen");

	pPostProcess1->AddComponent(new qPostScript);
	pPostProcess1->AddComponent(new qTransform);
	pPostProcess1->Transform()->SetRelativePos(Vec3(-4910.f, 0.f, 1.f));
	pPostProcess1->Transform()->SetRelativeScale(Vec3(1600.f, 900.f, 0.f));

	pPostProcess1->AddComponent(new qMeshRender);
	pPostProcess1->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pPostProcess1->MeshRender()->SetMaterial(pMtrl);

	pPostProcess1->AddComponent(new qFlipBookComponent);


	Ptr<qFlipBook> pPostOpen = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\postopen.flip");
	pPostProcess1->FlipBookComponent()->AddFlipBook(5, pPostOpen);

	pPostProcess1->AddComponent(new qFSM);
	pPostProcess1->FSM()->AddState(L"PostOpen", new qPostOpenState);
	

	pPostProcess1->FSM()->ChangeState(L"PostOpen");

	pStage2->AddObject(9, pPostProcess1);




	qGameObject* pPostProcess2 = new qGameObject;
	pPostProcess2->SetName(L"PostClose");

	pPostProcess2->AddComponent(new qPostScript);
	pPostProcess2->AddComponent(new qTransform);

	pPostProcess2->AddComponent(new qMeshRender);
	pPostProcess2->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pPostProcess2->MeshRender()->SetMaterial(pAlphaBlendMtrl);

	pPostProcess2->AddComponent(new qFlipBookComponent);

	Ptr<qFlipBook> pPostClose = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\chang.flip");
	pPostProcess2->FlipBookComponent()->AddFlipBook(4, pPostClose);


	pPostProcess2->AddComponent(new qFSM);
	pPostProcess2->FSM()->AddState(L"PostClose", new qPostCloseState);

	pStage2->AddObject(9, pPostProcess2);



	// ===============
	//	   PLAYER
	// ===============
	
	qGameObject* pPlayer = new qGameObject;
	pPlayer->SetName(L"Player");
	pPlayer->AddComponent(new qPlayerScript);
	//pPlayer->AddChild(pLightPlayer);

	pPlayer->AddComponent(new qTransform);
	pPlayer->Transform()->SetRelativePos(-4910.f, -200.f, 10.f);
	pPlayer->Transform()->SetRelativeScale(130.f, 130.f, 1.f);

	pPlayer->AddComponent(new qMeshRender);
	pPlayer->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pPlayer->MeshRender()->SetMaterial(pMtrl);

	pPlayer->AddComponent(new qFlipBookComponent);

	Ptr<qFlipBook> pDeathIdle = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\death_idle_right.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(0, pDeathIdle);

	Ptr<qFlipBook> pDeathWait = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\wait.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(1, pDeathWait);

	Ptr<qFlipBook> pDeathRun = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\death_run.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(2, pDeathRun);

	Ptr<qFlipBook> pDeathIdleToRun = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\idletorun_2.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(3, pDeathIdleToRun);

	Ptr<qFlipBook> pDeathRunToIdle = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\runtoidle.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(4, pDeathRunToIdle);

	Ptr<qFlipBook> pDeathIdleUTurn = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\idleuturn_2.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(5, pDeathIdleUTurn);

	Ptr<qFlipBook> pDeathRunUTurn = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\runuturn.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(6, pDeathRunUTurn);

	Ptr<qFlipBook> pDeathJump = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\jump_3.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(7, pDeathJump);

	Ptr<qFlipBook> pDeathFalling = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\falling.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(8, pDeathFalling);

	Ptr<qFlipBook> pDeathLanding = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\landing.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(9, pDeathLanding);

	Ptr<qFlipBook> pDeathDash = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\dash_3.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(10, pDeathDash);

	Ptr<qFlipBook> pDeathElevatorOut = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\eleout1.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(11, pDeathElevatorOut);

	Ptr<qFlipBook> pDeathGetItem = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\getitem_2.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(12, pDeathGetItem);

	Ptr<qFlipBook> pDeathCombo1 = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\combo1_final.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(13, pDeathCombo1);

	Ptr<qFlipBook> pDeathCombo2 = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\combo2_final.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(14, pDeathCombo2);

	Ptr<qFlipBook> pDeathCombo3 = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\combo3_f.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(15, pDeathCombo3);

	Ptr<qFlipBook> pDeathCombo4 = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\combo4_finalx.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(16, pDeathCombo4);

	Ptr<qFlipBook> pDeathBookShoot = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\bookshoot.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(17, pDeathBookShoot);

	Ptr<qFlipBook> pDeathCrash = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\crash_final.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(19, pDeathCrash);

	Ptr<qFlipBook> pDeathRange = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\range_test2.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(20, pDeathRange);

	Ptr<qFlipBook> pDeathKrush = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\krush_final.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(21, pDeathKrush);

	Ptr<qFlipBook> pDeathTeleport = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\teleport.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(22, pDeathTeleport);

	Ptr<qFlipBook> pDeathTeleportFinish = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\playernull.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(23, pDeathTeleportFinish);

	Ptr<qFlipBook> pDeathBump = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\hit.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(24, pDeathBump);

	Ptr<qFlipBook> pDeathNull = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\playernull.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(25, pDeathNull);

	//pPlayer->FlipBookComponent()->Play(0, 10, true);

	pPlayer->AddComponent(new qRigidBody);
	pPlayer->RigidBody()->SetMass(1.f);
	pPlayer->RigidBody()->SetMaxWalkSpeed(300.f);
	pPlayer->RigidBody()->SetFriction(100.f);
	pPlayer->RigidBody()->UseGravity(true);
	pPlayer->RigidBody()->SetMaxGravitySpeed(1500.f);
	pPlayer->RigidBody()->SetJumpSpeed(400.f);
	pPlayer->RigidBody()->SetGround(true);
	pPlayer->RigidBody()->SetWall(false);

	pPlayer->AddComponent(new qCollider2D);
	pPlayer->Collider2D()->SetIndependentScale(false);
	pPlayer->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlayer->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	// FSM
	pPlayer->AddComponent(new qFSM);

	pPlayer->FSM()->AddState(L"Idle", new qPlayerIdleState);				// 0
	pPlayer->FSM()->AddState(L"Wait", new qPlayerWaitState);				// 1
	pPlayer->FSM()->AddState(L"Run", new qPlayerRunState);					// 2
	pPlayer->FSM()->AddState(L"IdleToRun", new qPlayerIdleToRunState);		// 3
	pPlayer->FSM()->AddState(L"RunToIdle", new qPlayerRunToIdleState);		// 4
	pPlayer->FSM()->AddState(L"IdleUTurn", new qPlayerIdleUTurnState);		// 5
	pPlayer->FSM()->AddState(L"RunUTurn", new qPlayerRunUTurnState);		// 6
	pPlayer->FSM()->AddState(L"Jump", new qPlayerJumpState);				// 7
	pPlayer->FSM()->AddState(L"Falling", new qPlayerFallingState);			// 8
	pPlayer->FSM()->AddState(L"Landing", new qPlayerLandingState);			// 9
	pPlayer->FSM()->AddState(L"Dash", new qPlayerDashState);				// 10
	pPlayer->FSM()->AddState(L"ElevatorOut", new qPlayerElevatorOutState);	// 11
	pPlayer->FSM()->AddState(L"GetItem", new qPlayerGetItemState);			// 12
	pPlayer->FSM()->AddState(L"Combo1", new qPlayerCombo1State);			// 13
	pPlayer->FSM()->AddState(L"Combo2", new qPlayerCombo2State);			// 14
	pPlayer->FSM()->AddState(L"Combo3", new qPlayerCombo3State);			// 15
	pPlayer->FSM()->AddState(L"Combo4", new qPlayerCombo4State);			// 16
	pPlayer->FSM()->AddState(L"BookShoot", new qPlayerBookShootState);		// 17

	pPlayer->FSM()->AddState(L"Crash", new qPlayerCrashState);				// 19
	pPlayer->FSM()->AddState(L"Range", new qPlayerRangeState);				// 20
	pPlayer->FSM()->AddState(L"Krush", new qPlayerKrushState);				// 21

	pPlayer->FSM()->AddState(L"Teleport", new qPlayerTeleportState);		// 22
	pPlayer->FSM()->AddState(L"TeleportFinish", new qPlayerTeleportFinishState);	// 23

	pPlayer->FSM()->AddState(L"Bump", new qPlayerBumpState);				// 24
	pPlayer->FSM()->AddState(L"Null", new qPlayerNullState);				// 25

	//pPlayer->FSM()->ChangeState(L"Idle");

	pStage2->AddObject(3, pPlayer);



	// ========================
	//          MONSTER
	// ========================

	// =============
	//    스켈레톤
	// =============

	// 스켈레톤 1
	qGameObject* pSkeleton1 = new qGameObject;
	pSkeleton1->SetName(L"Skeleton");

	pSkeleton1->AddComponent(new qSkeletonScript);

	pSkeleton1->AddComponent(new qMeshRender);
	pSkeleton1->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pSkeleton1->MeshRender()->SetMaterial(pMtrl);

	pSkeleton1->AddComponent(new qTransform);
	pSkeleton1->Transform()->SetRelativePos(-3830.f, -580.f, 30.f);
	pSkeleton1->Transform()->SetRelativeScale(170.f, 160.f, 1.f);

	pSkeleton1->AddComponent(new qCollider2D);
	pSkeleton1->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pSkeleton1->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	pSkeleton1->AddComponent(new qFlipBookComponent);

	Ptr<qFlipBook> pSkeletonIdle = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\skeleton_idle.flip");
	pSkeleton1->FlipBookComponent()->AddFlipBook(0, pSkeletonIdle);

	Ptr<qFlipBook> pSkeletonAttack = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\skeleton_attack.flip");
	pSkeleton1->FlipBookComponent()->AddFlipBook(1, pSkeletonAttack);

	Ptr<qFlipBook> pSkeletonDeath = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\skeleton_death.flip");
	pSkeleton1->FlipBookComponent()->AddFlipBook(2, pSkeletonDeath);

	pSkeleton1->AddComponent(new qFSM);
	pSkeleton1->FSM()->AddState(L"SkeletonIdle", new qSkeletonIdleState);		// 0
	pSkeleton1->FSM()->AddState(L"SkeletonAttack", new qSkeletonAttackState);	// 1
	pSkeleton1->FSM()->AddState(L"SkeletonDeath", new qSkeletonDeathState);		// 2
	pSkeleton1->FSM()->ChangeState(L"SkeletonIdle");

	pStage2->AddObject(5, pSkeleton1);



	// 스켈레톤 2
	qGameObject* pSkeleton2 = new qGameObject;
	pSkeleton2->SetName(L"Skeleton");

	pSkeleton2->AddComponent(new qSkeletonScript);

	pSkeleton2->AddComponent(new qMeshRender);
	pSkeleton2->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pSkeleton2->MeshRender()->SetMaterial(pMtrl);

	pSkeleton2->AddComponent(new qTransform);
	pSkeleton2->Transform()->SetRelativePos(-3235.f, -390.f, 30.f);
	pSkeleton2->Transform()->SetRelativeScale(170.f, 160.f, 1.f);

	pSkeleton2->AddComponent(new qCollider2D);
	pSkeleton2->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pSkeleton2->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	pSkeleton2->AddComponent(new qFlipBookComponent);

	pSkeleton2->FlipBookComponent()->AddFlipBook(0, pSkeletonIdle);
	pSkeleton2->FlipBookComponent()->AddFlipBook(1, pSkeletonAttack);
	pSkeleton2->FlipBookComponent()->AddFlipBook(2, pSkeletonDeath);

	pSkeleton2->AddComponent(new qFSM);
	pSkeleton2->FSM()->AddState(L"SkeletonIdle", new qSkeletonIdleState);		// 0
	pSkeleton2->FSM()->AddState(L"SkeletonAttack", new qSkeletonAttackState);	// 1
	pSkeleton2->FSM()->AddState(L"SkeletonDeath", new qSkeletonDeathState);		// 2
	pSkeleton2->FSM()->ChangeState(L"SkeletonIdle");

	pStage2->AddObject(5, pSkeleton2);


	// 스켈레톤 3
	qGameObject* pSkeleton3 = new qGameObject;
	pSkeleton3->SetName(L"Skeleton");

	pSkeleton3->AddComponent(new qSkeletonScript);

	pSkeleton3->AddComponent(new qMeshRender);
	pSkeleton3->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pSkeleton3->MeshRender()->SetMaterial(pMtrl);

	pSkeleton3->AddComponent(new qTransform);
	pSkeleton3->Transform()->SetRelativePos(-2850.f, -66.f, 30.f);
	pSkeleton3->Transform()->SetRelativeScale(170.f, 160.f, 1.f);

	pSkeleton3->AddComponent(new qCollider2D);
	pSkeleton3->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pSkeleton3->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	pSkeleton3->AddComponent(new qFlipBookComponent);

	pSkeleton3->FlipBookComponent()->AddFlipBook(0, pSkeletonIdle);
	pSkeleton3->FlipBookComponent()->AddFlipBook(1, pSkeletonAttack);
	pSkeleton3->FlipBookComponent()->AddFlipBook(2, pSkeletonDeath);

	pSkeleton3->AddComponent(new qFSM);
	pSkeleton3->FSM()->AddState(L"SkeletonIdle", new qSkeletonIdleState);		// 0
	pSkeleton3->FSM()->AddState(L"SkeletonAttack", new qSkeletonAttackState);	// 1
	pSkeleton3->FSM()->AddState(L"SkeletonDeath", new qSkeletonDeathState);		// 2
	pSkeleton3->FSM()->ChangeState(L"SkeletonIdle");

	pStage2->AddObject(5, pSkeleton3);


	// 스켈레톤 4
	qGameObject* pSkeleton4 = new qGameObject;
	pSkeleton4->SetName(L"Skeleton");

	pSkeleton4->AddComponent(new qSkeletonScript);

	pSkeleton4->AddComponent(new qMeshRender);
	pSkeleton4->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pSkeleton4->MeshRender()->SetMaterial(pMtrl);

	pSkeleton4->AddComponent(new qTransform);
	pSkeleton4->Transform()->SetRelativePos(-877.f, 151.f, 30.f);
	pSkeleton4->Transform()->SetRelativeScale(170.f, 160.f, 1.f);

	pSkeleton4->AddComponent(new qCollider2D);
	pSkeleton4->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pSkeleton4->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	pSkeleton4->AddComponent(new qFlipBookComponent);

	pSkeleton4->FlipBookComponent()->AddFlipBook(0, pSkeletonIdle);
	pSkeleton4->FlipBookComponent()->AddFlipBook(1, pSkeletonAttack);
	pSkeleton4->FlipBookComponent()->AddFlipBook(2, pSkeletonDeath);

	pSkeleton4->AddComponent(new qFSM);
	pSkeleton4->FSM()->AddState(L"SkeletonIdle", new qSkeletonIdleState);		// 0
	pSkeleton4->FSM()->AddState(L"SkeletonAttack", new qSkeletonAttackState);	// 1
	pSkeleton4->FSM()->AddState(L"SkeletonDeath", new qSkeletonDeathState);		// 2
	pSkeleton4->FSM()->ChangeState(L"SkeletonIdle");

	pStage2->AddObject(5, pSkeleton4);


	// 스켈레톤 5
	qGameObject* pSkeleton5 = new qGameObject;
	pSkeleton5->SetName(L"Skeleton");

	pSkeleton5->AddComponent(new qSkeletonScript);

	pSkeleton5->AddComponent(new qMeshRender);
	pSkeleton5->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pSkeleton5->MeshRender()->SetMaterial(pMtrl);

	pSkeleton5->AddComponent(new qTransform);
	pSkeleton5->Transform()->SetRelativePos(196.f, -202.f, 30.f);
	pSkeleton5->Transform()->SetRelativeScale(170.f, 160.f, 1.f);

	pSkeleton5->AddComponent(new qCollider2D);
	pSkeleton5->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pSkeleton5->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	pSkeleton5->AddComponent(new qFlipBookComponent);

	pSkeleton5->FlipBookComponent()->AddFlipBook(0, pSkeletonIdle);
	pSkeleton5->FlipBookComponent()->AddFlipBook(1, pSkeletonAttack);
	pSkeleton5->FlipBookComponent()->AddFlipBook(2, pSkeletonDeath);

	pSkeleton5->AddComponent(new qFSM);
	pSkeleton5->FSM()->AddState(L"SkeletonIdle", new qSkeletonIdleState);		// 0
	pSkeleton5->FSM()->AddState(L"SkeletonAttack", new qSkeletonAttackState);	// 1
	pSkeleton5->FSM()->AddState(L"SkeletonDeath", new qSkeletonDeathState);		// 2
	pSkeleton5->FSM()->ChangeState(L"SkeletonIdle");

	pStage2->AddObject(5, pSkeleton5);


	// =============
	//	   익사
	// =============


	// 익사 1
	qGameObject* pDrowned1 = new qGameObject;
	pDrowned1->SetName(L"Drowned");
	pDrowned1->AddComponent(new qDrownedScript);

	pDrowned1->AddComponent(new qMeshRender);
	pDrowned1->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pDrowned1->MeshRender()->SetMaterial(pAlphaBlendMtrl);

	pDrowned1->AddComponent(new qTransform);
	pDrowned1->Transform()->SetRelativePos(-2200.f, 325.f, 30.f);
	pDrowned1->Transform()->SetRelativeScale(150.f, 230.f, 1.f);


	pDrowned1->AddComponent(new qCollider2D);
	pDrowned1->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pDrowned1->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	pDrowned1->AddComponent(new qFlipBookComponent);
	Ptr<qFlipBook> pDrownedIdle = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\drowned_idle_ice.flip");
	pDrowned1->FlipBookComponent()->AddFlipBook(0, pDrownedIdle);

	Ptr<qFlipBook> pDrownedRun = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\drowned_run_ice.flip");
	pDrowned1->FlipBookComponent()->AddFlipBook(1, pDrownedRun);

	Ptr<qFlipBook> pDrownedUturn = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\drowned_uturn_ice.flip");
	pDrowned1->FlipBookComponent()->AddFlipBook(2, pDrownedUturn);

	Ptr<qFlipBook> pDrownedAttack = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\drowned_attack_ice2.flip");
	pDrowned1->FlipBookComponent()->AddFlipBook(3, pDrownedAttack);

	Ptr<qFlipBook> pDrownedHit = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\drowned_hit_ice.flip");
	pDrowned1->FlipBookComponent()->AddFlipBook(4, pDrownedHit);

	Ptr<qFlipBook> pDrownedDeath = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\drowned_death_ice.flip");
	pDrowned1->FlipBookComponent()->AddFlipBook(5, pDrownedDeath);

	pDrowned1->AddComponent(new qFSM);
	pDrowned1->FSM()->AddState(L"DrownedIdle", new qDrownedIdleState);			// 0
	pDrowned1->FSM()->AddState(L"DrownedRun", new qDrownedRunState);			// 1
	pDrowned1->FSM()->AddState(L"DrownedUturn", new qDrownedUturnState);		// 2
	pDrowned1->FSM()->AddState(L"DrownedAttack", new qDrownedAttackState);		// 3
	pDrowned1->FSM()->AddState(L"DrownedHit", new qDrownedHitState);			// 4
	pDrowned1->FSM()->AddState(L"DrownedDeath", new qDrownedDeathState);		// 5

	pDrowned1->FSM()->ChangeState(L"DrownedIdle");

	pStage2->AddObject(5, pDrowned1);


	// 익사 2
	qGameObject* pDrowned2 = new qGameObject;
	pDrowned2->SetName(L"Drowned");
	pDrowned2->AddComponent(new qDrownedScript);

	pDrowned2->AddComponent(new qMeshRender);
	pDrowned2->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pDrowned2->MeshRender()->SetMaterial(pAlphaBlendMtrl);

	pDrowned2->AddComponent(new qTransform);
	pDrowned2->Transform()->SetRelativePos(-363.f, -312.f, 30.f);
	pDrowned2->Transform()->SetRelativeScale(150.f, 230.f, 1.f);


	pDrowned2->AddComponent(new qCollider2D);
	pDrowned2->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pDrowned2->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	pDrowned2->AddComponent(new qFlipBookComponent);
	
	pDrowned2->FlipBookComponent()->AddFlipBook(0, pDrownedIdle);
	pDrowned2->FlipBookComponent()->AddFlipBook(1, pDrownedRun);
	pDrowned2->FlipBookComponent()->AddFlipBook(2, pDrownedUturn);
	pDrowned2->FlipBookComponent()->AddFlipBook(3, pDrownedAttack);
	pDrowned2->FlipBookComponent()->AddFlipBook(4, pDrownedHit);
	pDrowned2->FlipBookComponent()->AddFlipBook(5, pDrownedDeath);

	pDrowned2->AddComponent(new qFSM);
	pDrowned2->FSM()->AddState(L"DrownedIdle", new qDrownedIdleState);			// 0
	pDrowned2->FSM()->AddState(L"DrownedRun", new qDrownedRunState);			// 1
	pDrowned2->FSM()->AddState(L"DrownedUturn", new qDrownedUturnState);		// 2
	pDrowned2->FSM()->AddState(L"DrownedAttack", new qDrownedAttackState);		// 3
	pDrowned2->FSM()->AddState(L"DrownedHit", new qDrownedHitState);			// 4
	pDrowned2->FSM()->AddState(L"DrownedDeath", new qDrownedDeathState);		// 5

	pDrowned2->FSM()->ChangeState(L"DrownedIdle");

	pStage2->AddObject(5, pDrowned2);



	// =============
	//	   고스트
	// =============


	// Ghost 1
	qGameObject* pGhost1 = new qGameObject;
	pGhost1->SetName(L"Ghost");
	pGhost1->AddComponent(new qGhostScript);

	pGhost1->AddComponent(new qMeshRender);
	pGhost1->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pGhost1->MeshRender()->SetMaterial(pAlphaBlendMtrl);

	pGhost1->AddComponent(new qTransform);
	pGhost1->Transform()->SetRelativePos(-1960.f, -23.f, 30.f);
	pGhost1->Transform()->SetRelativeScale(200.f, 250.f, 1.f);


	pGhost1->AddComponent(new qCollider2D);
	pGhost1->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pGhost1->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	pGhost1->AddComponent(new qFlipBookComponent);
	
	Ptr<qFlipBook> pGhostIdle = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\ghost_idle.flip");
	pGhost1->FlipBookComponent()->AddFlipBook(0, pGhostIdle);

	Ptr<qFlipBook> pGhostRun = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\ghost_run.flip");
	pGhost1->FlipBookComponent()->AddFlipBook(1, pGhostRun);

	Ptr<qFlipBook> pGhostUturn = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\ghost_uturn.flip");
	pGhost1->FlipBookComponent()->AddFlipBook(2, pGhostUturn);

	Ptr<qFlipBook> pGhostAttack = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\ghost_attack.flip");
	pGhost1->FlipBookComponent()->AddFlipBook(3, pGhostAttack);

	Ptr<qFlipBook> pGhostHit = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\ghost_hit.flip");
	pGhost1->FlipBookComponent()->AddFlipBook(4, pGhostHit);
	
	Ptr<qFlipBook> pGhostDeath = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\ghost_death.flip");
	pGhost1->FlipBookComponent()->AddFlipBook(5, pGhostDeath);

	pGhost1->AddComponent(new qFSM);
	pGhost1->FSM()->AddState(L"GhostIdle", new qGhostIdleState);			// 0
	pGhost1->FSM()->AddState(L"GhostRun", new qGhostRunState);				// 1
	pGhost1->FSM()->AddState(L"GhostUturn", new qGhostUturnState);			// 2
	pGhost1->FSM()->AddState(L"GhostAttack", new qGhostAttackState);		// 3
	pGhost1->FSM()->AddState(L"GhostHit", new qGhostHitState);				// 4
	pGhost1->FSM()->AddState(L"GhostDeath", new qGhostDeathState);			// 5

	pGhost1->FSM()->ChangeState(L"GhostIdle");

	pStage2->AddObject(5, pGhost1);


	// Ghost 2
	qGameObject* pGhost2 = new qGameObject;
	pGhost2->SetName(L"Ghost");
	pGhost2->AddComponent(new qGhostScript);

	pGhost2->AddComponent(new qMeshRender);
	pGhost2->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pGhost2->MeshRender()->SetMaterial(pAlphaBlendMtrl);

	pGhost2->AddComponent(new qTransform);
	pGhost2->Transform()->SetRelativePos(967.f, 164.f, 30.f);
	pGhost2->Transform()->SetRelativeScale(200.f, 250.f, 1.f);


	pGhost2->AddComponent(new qCollider2D);
	pGhost2->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pGhost2->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	pGhost2->AddComponent(new qFlipBookComponent);
	pGhost2->FlipBookComponent()->AddFlipBook(0, pGhostIdle);	
	pGhost2->FlipBookComponent()->AddFlipBook(1, pGhostRun);	
	pGhost2->FlipBookComponent()->AddFlipBook(2, pGhostUturn);	
	pGhost2->FlipBookComponent()->AddFlipBook(3, pGhostAttack);
	pGhost2->FlipBookComponent()->AddFlipBook(4, pGhostHit);	
	pGhost2->FlipBookComponent()->AddFlipBook(5, pGhostDeath);

	pGhost2->AddComponent(new qFSM);
	pGhost2->FSM()->AddState(L"GhostIdle", new qGhostIdleState);			// 0
	pGhost2->FSM()->AddState(L"GhostRun", new qGhostRunState);				// 1
	pGhost2->FSM()->AddState(L"GhostUturn", new qGhostUturnState);			// 2
	pGhost2->FSM()->AddState(L"GhostAttack", new qGhostAttackState);		// 3
	pGhost2->FSM()->AddState(L"GhostHit", new qGhostHitState);				// 4
	pGhost2->FSM()->AddState(L"GhostDeath", new qGhostDeathState);			// 5

	pGhost2->FSM()->ChangeState(L"GhostIdle");

	pStage2->AddObject(5, pGhost2);


	//qGameObject* pMonster = new qGameObject;
	//pMonster->SetName(L"Monster");
	//
	//pMonster->AddComponent(new qTransform);
	//pMonster->AddComponent(new qCollider2D);
	//
	//pMonster->Transform()->SetRelativePos(-400.f, -420.f, 9.f);
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
	//
	//pMonster->MeshRender()->GetMaterial()->SetTexParam(TEX_0, qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\fire_11.png"));
	//
	//pStage2->AddObject(5, pMonster);



	// ITEM
	qGameObject* pItem = new qGameObject;
	pItem->SetName(L"Item");
	pItem->AddComponent(new qTransform);

	pItem->Transform()->SetRelativePos(3978.f, 94.f, 30.f);
	pItem->Transform()->SetRelativeScale(130.f, 130.f, 1.f);

	pItem->AddComponent(new qMeshRender);
	pItem->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pItem->MeshRender()->SetMaterial(pAlphaBlendMtrl);

	pItem->AddComponent(new qFlipBookComponent);

	Ptr<qFlipBook> pItemFlip = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\item.flip");
	pItem->FlipBookComponent()->AddFlipBook(0, pItemFlip);

	pItem->FlipBookComponent()->Play(0, 10, true);

	pItem->AddComponent(new qCollider2D);
	pItem->Collider2D()->SetIndependentScale(false);
	pItem->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pItem->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	pStage2->AddObject(14, pItem);



	// 충돌 지정
	//qCollisionMgr::GetInst()->CollisionCheck(2, 3);		// Platform vs Player
	//qCollisionMgr::GetInst()->CollisionCheck(2, 7);		// Platform vs Player
	//qCollisionMgr::GetInst()->CollisionCheck(4, 5);		// PlayerSkill vs Monster
	//qCollisionMgr::GetInst()->CollisionCheck(4, 7);		// PlayerSkill vs Boss
	//qCollisionMgr::GetInst()->CollisionCheck(3, 5);		// Player vs Monster
	//qCollisionMgr::GetInst()->CollisionCheck(3, 6);		// Player vs Monster Skill
	//qCollisionMgr::GetInst()->CollisionCheck(3, 8);		// Player vs Boss Skill
	//qCollisionMgr::GetInst()->CollisionCheck(3, 9);		// Player vs Portal
	//qCollisionMgr::GetInst()->CollisionCheck(3, 11);	// Player vs Wall (Bump)
	//qCollisionMgr::GetInst()->CollisionCheck(3, 13);	// Player vs Clap
	//qCollisionMgr::GetInst()->CollisionCheck(3, 14);	// Player vs Item
	//qCollisionMgr::GetInst()->CollisionCheck(3, 7);		// Player vs Boss
	//
	//ChangeLevel(pStage2, LEVEL_STATE::STOP);

}
