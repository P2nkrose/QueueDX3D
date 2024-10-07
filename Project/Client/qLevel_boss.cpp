#include "pch.h"
#include "qLevel_boss.h"


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
#include <Scripts/qBookScript_Left.h>
#include <Scripts/qMissileScript.h>
#include <Scripts/qCameraMoveScript.h>
#include <Scripts/qPlatformScript.h>
#include <Scripts/qWallScript.h>
#include <Scripts/qPostScript.h>
#include <Scripts/qClapScript.h>

#include <Scripts/qBossScript.h>
#include <Scripts/qPunchScript.h>
#include <Scripts/qSlamScript.h>
#include <Scripts/qBleedScript.h>


#include <Engine/qSetColorCS.h>
#include <Engine/qStructuredBuffer.h>

#include <Scripts/qBossHUDScript.h>

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
//        Boss State                           * INDEX *
// ========================

#include <States/qBossIntroState.h>				// 0
#include <States/qBossIdleState.h>				// 1
#include <States/qBossRunState.h>				// 2
#include <States/qBossPunchState.h>				// 3
#include <States/qBossSlamState.h>				// 4
#include <States/qBossBleedState.h>				// 5
#include <States/qBossHitState.h>				// 6
#include <States/qBossDeathState.h>				// 7
#include <States/qBossStayState.h>				// 8


#include <States/qBossUturnState.h>				// 11

#include <States/qBossSlamFistState.h>			
#include <States/qBossBleedWaveState.h>			




// ========================                    
//      Transfer State                         * INDEX *
// ========================

#include <States/qPostCloseState.h>				// 4
#include <States/qPostOpenState.h>				// 5

#include <States/qElevatorStayState.h>			// 6
#include <States/qElevatorOpenState.h>			// 7
#include <States/qElevatorCloseState.h>			// 8

#include <States/qWarningState.h>	

#include "qLevelSaveLoad.h"

void qLevel_boss::CreateStageBoss()
{
	// Sound

	

	// Material
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	Ptr<qMaterial> pAlphaBlendMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DAlphaBlendMtrl");
	Ptr<qMaterial> pDebugShapeMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"DebugShapeMtrl");
	Ptr<qMaterial> pMtrl2 = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"material\\bossBack2.mtrl");




	// Level
	qLevel* pStageBoss = new qLevel;

	qLevelMgr::GetInst()->InsertLevel(L"stageboss", pStageBoss);

	pStageBoss->SetName(L"stageboss");

	pStageBoss->GetLayer(0)->SetName(L"Camera");
	pStageBoss->GetLayer(1)->SetName(L"Background");
	pStageBoss->GetLayer(2)->SetName(L"Platform");
	pStageBoss->GetLayer(3)->SetName(L"Player");
	pStageBoss->GetLayer(4)->SetName(L"PlayerSkill");
	pStageBoss->GetLayer(5)->SetName(L"Monster");
	pStageBoss->GetLayer(6)->SetName(L"MonsterSkill");
	pStageBoss->GetLayer(7)->SetName(L"Boss");
	pStageBoss->GetLayer(8)->SetName(L"BossSkill");
	pStageBoss->GetLayer(9)->SetName(L"Portal");
	pStageBoss->GetLayer(10)->SetName(L"Light");
	pStageBoss->GetLayer(11)->SetName(L"Wall");
	pStageBoss->GetLayer(12)->SetName(L"Effect");
	pStageBoss->GetLayer(13)->SetName(L"Clap");
	pStageBoss->GetLayer(14)->SetName(L"Item");
	pStageBoss->GetLayer(31)->SetName(L"UI");



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

	pStageBoss->AddObject(0, CameraObject);


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

	pStageBoss->AddObject(0, UICameraObject);


	// 광원 오브젝트
	qGameObject* pLightUI = new qGameObject;
	pLightUI->SetName(L"LightUI");
	pLightUI->AddComponent(new qTransform);
	pLightUI->AddComponent(new qLight2D);

	pLightUI->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	pLightUI->Light2D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	pLightUI->Light2D()->SetRadius(1000.f);



	// UI
	Ptr<qMaterial> pUIMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DUIMtrl");
	Ptr<qTexture> pUI = qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\UI\\UI.png");
	pUIMtrl->SetTexParam(TEX_0, pUI);

	qGameObject* UI = new qGameObject;
	UI->SetName(L"UI");
	//UI->AddChild(pLightUI);
	UI->AddComponent(new qTransform);
	UI->Transform()->SetRelativePos(0.f, -15.f, 30.f);
	UI->Transform()->SetRelativeScale(1600.f, 900.f, 1.f);


	UI->AddComponent(new qMeshRender);
	UI->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	UI->MeshRender()->SetMaterial(pUIMtrl);

	pStageBoss->AddObject(31, UI);


	// BOSS UI
	Ptr<qMaterial> pbossUIMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DBOSSUIMtrl");
	Ptr<qTexture> pbossUI = qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\UI\\bossUI.png");
	pbossUIMtrl->SetTexParam(TEX_0, pbossUI);
	
	qGameObject* bossUI = new qGameObject;
	bossUI->SetName(L"bossUI");
	//UI->AddChild(pLightUI);
	bossUI->AddComponent(new qTransform);
	bossUI->Transform()->SetRelativePos(100.f, 687.f, 10.f);
	//bossUI->Transform()->SetRelativeScale(1600.f, 900.f, 1.f);


	bossUI->AddComponent(new qMeshRender);
	bossUI->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	bossUI->MeshRender()->SetMaterial(pbossUIMtrl);
	
	pStageBoss->AddObject(31, bossUI);



	// Player HUD
	Ptr<qMaterial> pHUDMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DHUDMtrl");
	Ptr<qTexture> pPlayerHUDUI = qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\UI\\playerHUD.png");
	pHUDMtrl->SetTexParam(TEX_0, pPlayerHUDUI);


	qGameObject* PlayerHUD = new qGameObject;
	PlayerHUD->SetName(L"PlayerHUD");
	PlayerHUD->AddComponent(new qTransform);
	PlayerHUD->Transform()->SetRelativePos(-427.f, 372.f, 10.f);
	PlayerHUD->Transform()->SetRelativeScale(413.f, 10.f, 1.f);

	PlayerHUD->AddComponent(new qPlayerHUDScript);
	PlayerHUD->AddComponent(new qMeshRender);
	PlayerHUD->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));

	PlayerHUD->MeshRender()->SetMaterial(pHUDMtrl);

	pStageBoss->AddObject(31, PlayerHUD);


	// Boss HUD
	Ptr<qMaterial> pBOSSHUDMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DBOSSHUDMtrl");
	Ptr<qTexture> pBossHUDUI = qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\UI\\bossHUD.png");
	pBOSSHUDMtrl->SetTexParam(TEX_0, pBossHUDUI);


	qGameObject* BossHUD = new qGameObject;
	BossHUD->SetName(L"BossHUD");
	BossHUD->AddComponent(new qTransform);
	BossHUD->Transform()->SetRelativePos(24.f, 293.f, 1.f);
	//BossHUD->Transform()->SetRelativeScale(1127.f, 13.f, 1.f);

	BossHUD->AddComponent(new qBossHUDScript);
	BossHUD->AddComponent(new qMeshRender);
	BossHUD->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));

	BossHUD->MeshRender()->SetMaterial(pBOSSHUDMtrl);

	pStageBoss->AddObject(31, BossHUD);



	// 배경
	qGameObject* pBackground = new qGameObject;
	pBackground->SetName(L"BGstageboss");

	pBackground->AddComponent(new qTransform);
	pBackground->Transform()->SetRelativePos(0.f, 0.f, 50.f);
	pBackground->Transform()->SetRelativeScale(2400.f, 1270.f, 1.f);

	pBackground->AddComponent(new qMeshRender);
	pBackground->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pBackground->MeshRender()->SetMaterial(pMtrl2);

	pStageBoss->AddObject(1, pBackground);


	// 플랫폼
	qGameObject* pPlatform = new qGameObject;
	pPlatform->SetName(L"Platform");
	pPlatform->AddComponent(new qPlatformScript);

	pPlatform->AddComponent(new qTransform);
	pPlatform->Transform()->SetRelativePos(0.f, -353.f, 10.f);
	pPlatform->Transform()->SetRelativeScale(2410.f, 30.f, 1.f);

	pPlatform->AddComponent(new qCollider2D);
	pPlatform->Collider2D()->SetIndependentScale(false);
	pPlatform->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	pStageBoss->AddObject(2, pPlatform);



	// 광원오브젝트 - 맵 전체 태양광
	qGameObject* pLight = new qGameObject;
	pLight->SetName(L"PointLightMap");
	pLight->AddComponent(new qTransform);
	pLight->AddComponent(new qLight2D);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLight->Light2D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	pLight->Light2D()->SetRadius(500.f);

	pStageBoss->AddObject(0, pLight);


	// =============
	//   TRANSFER
	// =============

	// 엘리베이터
	qGameObject* pElevator3 = new qGameObject;
	pElevator3->SetName(L"pElevator3");
	//pElevator1->AddChild(pLightEle1);

	pElevator3->AddComponent(new qTransform);
	pElevator3->Transform()->SetRelativePos(-665.f, -200.f, 10.f);
	pElevator3->Transform()->SetRelativeScale(550.f, 400.f, 1.f);

	pElevator3->AddComponent(new qMeshRender);
	pElevator3->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pElevator3->MeshRender()->SetMaterial(pAlphaBlendMtrl);

	pElevator3->AddComponent(new qFlipBookComponent);

	Ptr<qFlipBook> pElevatorStay = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\elevatorstay.flip");
	pElevator3->FlipBookComponent()->AddFlipBook(6, pElevatorStay);

	Ptr<qFlipBook> pElevatorOpen = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\elevatoropen.flip");
	pElevator3->FlipBookComponent()->AddFlipBook(7, pElevatorOpen);

	pElevator3->FlipBookComponent()->Play(7, 15, false);

	pElevator3->AddComponent(new qFSM);

	pElevator3->FSM()->AddState(L"ElevatorStay", new qElevatorStayState);		// 6
	pElevator3->FSM()->AddState(L"ElevatorOpen", new qElevatorOpenState);		// 7
	pElevator3->FSM()->AddState(L"ElevatorClose", new qElevatorCloseState);		// 8


	pElevator3->FSM()->ChangeState(L"ElevatorOpen");

	pStageBoss->AddObject(9, pElevator3);



	// WARNING EFFECT
	qGameObject* pWarning = new qGameObject;
	pWarning->SetName(L"Warning");

	pWarning->AddComponent(new qTransform);
	pWarning->Transform()->SetRelativePos(390.f, 0.f, 1.f);
	//pWarning->Transform()->SetRelativeScale(Vec3(1600.f, 900.f, 0.f));

	pWarning->AddComponent(new qMeshRender);
	pWarning->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pWarning->MeshRender()->SetMaterial(pAlphaBlendMtrl);

	pWarning->AddComponent(new qFlipBookComponent);

	Ptr<qFlipBook> pWarningFlip = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\warning.flip");
	pWarning->FlipBookComponent()->AddFlipBook(0, pWarningFlip);

	pWarning->AddComponent(new qFSM);
	pWarning->FSM()->AddState(L"WarningFlip", new qWarningState);

	pStageBoss->AddObject(12, pWarning);


	// Post Process
	qGameObject* pPostProcess1 = new qGameObject;
	pPostProcess1->SetName(L"PostOpen");
	
	pPostProcess1->AddComponent(new qPostScript);
	pPostProcess1->AddComponent(new qTransform);
	pPostProcess1->Transform()->SetRelativePos(Vec3(-390.f, -22.f, 30.f));
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
	
	pStageBoss->AddObject(9, pPostProcess1);




	// =============
	//    Player
	// =============

	qGameObject* pPlayer = new qGameObject;
	pPlayer->SetName(L"Player");

	pPlayer->AddComponent(new qPlayerScript);

	pPlayer->AddComponent(new qTransform);
	pPlayer->Transform()->SetRelativePos(-650.f, -273.f, 10.f);
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
	pPlayer->RigidBody()->SetGround(false);


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

	pStageBoss->AddObject(3, pPlayer);



	// ==============
	//     BOSS
	// ==============

	qGameObject* pBoss = new qGameObject;
	pBoss->SetName(L"Boss");
	pBoss->AddComponent(new qBossScript);

	pBoss->AddComponent(new qTransform);
	pBoss->Transform()->SetRelativePos(880.f, -186.f, 30.f);
	pBoss->Transform()->SetRelativeScale(500.f, 300.f, 1.f);

	pBoss->AddComponent(new qMeshRender);
	pBoss->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pBoss->MeshRender()->SetMaterial(pMtrl);

	pBoss->AddComponent(new qFlipBookComponent);

	Ptr<qFlipBook> pBossIntro = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\boss_intro.flip");
	pBoss->FlipBookComponent()->AddFlipBook(0, pBossIntro);

	Ptr<qFlipBook> pBossIdle = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\boss_idle.flip");
	pBoss->FlipBookComponent()->AddFlipBook(1, pBossIdle);

	Ptr<qFlipBook> pBossRun = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\boss_run.flip");
	pBoss->FlipBookComponent()->AddFlipBook(2, pBossRun);

	Ptr<qFlipBook> pBossPunch = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\boss_punch.flip");
	pBoss->FlipBookComponent()->AddFlipBook(3, pBossPunch);

	Ptr<qFlipBook> pBossSlam = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\boss_slam4.flip");
	pBoss->FlipBookComponent()->AddFlipBook(4, pBossSlam);

	Ptr<qFlipBook> pBossBleed = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\boss_bleed2.flip");
	pBoss->FlipBookComponent()->AddFlipBook(5, pBossBleed);

	Ptr<qFlipBook> pBossHit = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\boss_hit.flip");
	pBoss->FlipBookComponent()->AddFlipBook(6, pBossHit);

	Ptr<qFlipBook> pBossDeath = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\boss_death.flip");
	pBoss->FlipBookComponent()->AddFlipBook(7, pBossDeath);

	Ptr<qFlipBook> pBossStay = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\boss_stay.flip");
	pBoss->FlipBookComponent()->AddFlipBook(8, pBossStay);

	Ptr<qFlipBook> pBossUturn = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\boss_uturn.flip");
	pBoss->FlipBookComponent()->AddFlipBook(9, pBossUturn);


	pBoss->AddComponent(new qCollider2D);
	pBoss->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pBoss->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	//pBoss->Collider2D()->SetScale(Vec3(0.5f, 0.9f, 0.f));
	//pBoss->Collider2D()->SetOffset(Vec3(0.15f, -0.02f, 0.f));

	//pBoss->AddComponent(new qRigidBody);
	//pBoss->RigidBody()->SetMass(1.f);
	//pBoss->RigidBody()->SetMaxWalkSpeed(300.f);
	//pBoss->RigidBody()->SetFriction(100.f);
	//pBoss->RigidBody()->UseGravity(true);
	//pBoss->RigidBody()->SetMaxGravitySpeed(1500.f);
	//pBoss->RigidBody()->SetGround(false);




	// FSM
	pBoss->AddComponent(new qFSM);

	pBoss->FSM()->AddState(L"BossIntro", new qBossIntroState);			// 0
	pBoss->FSM()->AddState(L"BossIdle", new qBossIdleState);			// 1
	pBoss->FSM()->AddState(L"BossRun", new qBossRunState);				// 2
	pBoss->FSM()->AddState(L"BossPunch", new qBossPunchState);			// 3
	pBoss->FSM()->AddState(L"BossSlam", new qBossSlamState);			// 4
	pBoss->FSM()->AddState(L"BossBleed", new qBossBleedState);			// 5
	pBoss->FSM()->AddState(L"BossHit", new qBossHitState);				// 6
	pBoss->FSM()->AddState(L"BossDeath", new qBossDeathState);			// 7
	pBoss->FSM()->AddState(L"BossStay", new qBossStayState);			// 8
	pBoss->FSM()->AddState(L"BossUturn", new qBossUturnState);			// 9

	//pBoss->FSM()->ChangeState(L"BossIdle");

	pStageBoss->AddObject(7, pBoss);



	// CLAP
	qGameObject* pClap = new qGameObject;
	pClap->SetName(L"Clap");
	pClap->AddComponent(new qClapScript);
	pClap->AddComponent(new qTransform);
	pClap->Transform()->SetRelativePos(-110.f, -53.f, 10.f);
	pClap->Transform()->SetRelativeScale(27.f, 565.f, 1.f);
	pClap->AddComponent(new qCollider2D);
	pClap->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	pStageBoss->AddObject(13, pClap);





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
	//ChangeLevel(pStageBoss, LEVEL_STATE::STOP);


}
