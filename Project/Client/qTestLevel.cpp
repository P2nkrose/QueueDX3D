#include "pch.h"
#include "qTestLevel.h"

#include <Engine/qAssetMgr.h>
#include <Engine/assets.h>

#include <Engine/qCollisionMgr.h>
#include <Engine/qLevelMgr.h>

#include <Engine/qLevel.h>
#include <Engine/qLayer.h>
#include <Engine/qGameObject.h>
#include <Engine/components.h>

#include <Scripts/qPlayerScript.h>
#include <Scripts/qMissileScript.h>
#include <Scripts/qCameraMoveScript.h>

#include <Engine/qSetColorCS.h>
#include <Engine/qStructuredBuffer.h>

#include "qLevelSaveLoad.h"

void qTestLevel::CreateTestLevel()
{
	// Material
	Ptr<qMaterial> pStd3DMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std3DMtrl");
	Ptr<qMaterial> pStd3D_DeferredMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std3D_DeferredMtrl");
	

	// Level 생성
	qLevel* pLevel = new qLevel;
	pLevel->SetName(L"testlevel");

	qLevelMgr::GetInst()->InsertLevel(L"testlevel", pLevel);

	//ChangeLevel(pLevel, LEVEL_STATE::STOP);

	pLevel->GetLayer(0)->SetName(L"Default");
	pLevel->GetLayer(1)->SetName(L"Background");
	pLevel->GetLayer(2)->SetName(L"Platform");
	pLevel->GetLayer(3)->SetName(L"Player");
	pLevel->GetLayer(4)->SetName(L"Monster");
	pLevel->GetLayer(5)->SetName(L"PlayerProjectile");		// 플레이어 투사체
	pLevel->GetLayer(6)->SetName(L"MonsterProjectile");		// 몬스터 투사체
	pLevel->GetLayer(7)->SetName(L"Tile");					


	// 카메라 오브젝트
	qGameObject* CamObj = new qGameObject;
	CamObj->SetName(L"MainCamera");
	CamObj->AddComponent(new qTransform);
	CamObj->AddComponent(new qCamera);
	CamObj->AddComponent(new qCameraMoveScript);

	// 우선순위를 0 : Main Camera로 설정
	CamObj->Camera()->SetPriority(0);

	// 카메라 레이어 설정 (31번 레이어 제외 모든 레이어를 촬영)
	CamObj->Camera()->SetLayerAll();
	CamObj->Camera()->SetLayer(31, false);
	CamObj->Camera()->SetFar(100000.f);
	CamObj->Camera()->SetProjType(PERSPECTIVE);

	pLevel->AddObject(0, CamObj);


	qGameObject* pObject = nullptr;

	// 3D 광원 추가
	//pObject = new qGameObject;
	//pObject->SetName(L"Point Light");
	//pObject->AddComponent(new qTransform);
	//pObject->AddComponent(new qLight3D);
	//
	//pObject->Transform()->SetRelativePos(-100.f, -300.f, 0.f);
	//pObject->Transform()->SetRelativeRotation(XM_PI / 4.f, XM_PI / 4.f, 0.f);
	//
	//pObject->Light3D()->SetLightType(LIGHT_TYPE::POINT);
	//pObject->Light3D()->SetLightColor(Vec3(0.9f, 0.9f, 0.9f));
	//pObject->Light3D()->SetLightAmbient(Vec3(0.f, 0.f, 0.f));
	//pObject->Light3D()->SetSpecularCoefficient(0.3f);
	//pObject->Light3D()->SetRadius(500.f);
	//
	//pLevel->AddObject(0, pObject);

	pObject = new qGameObject;
	pObject->SetName(L"Directional Light");
	pObject->AddComponent(new qTransform);
	pObject->AddComponent(new qLight3D);

	pObject->Transform()->SetRelativePos(-100.f, -300.f, 0.f);
	pObject->Transform()->SetRelativeRotation(XM_PI / 4.f, XM_PI / 4.f, 0.f);

	pObject->Light3D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pObject->Light3D()->SetLightColor(Vec3(0.9f, 0.9f, 0.9f));
	pObject->Light3D()->SetLightAmbient(Vec3(0.f, 0.f, 0.f));
	pObject->Light3D()->SetSpecularCoefficient(0.3f);
	pObject->Light3D()->SetRadius(400.f);

	pLevel->AddObject(0, pObject);

	//// Point Light 하나 더 추가
	//pObject = pObject->Clone();
	//pObject->Transform()->SetRelativePos(100.f, -300.f, 0.f);
	//pLevel->AddObject(0, pObject);



	//// 3D 광원 추가
	//pObject = new qGameObject;
	//pObject->SetName(L"Point Light 2");
	//pObject->AddComponent(new qTransform);
	//pObject->AddComponent(new qLight3D);
	//
	//pObject->Transform()->SetRelativePos(300.f, 0.f, 0.f);
	//pObject->Transform()->SetRelativeRotation(XM_PI / 4.f, XM_PI / 4.f, 0.f);
	//
	//pObject->Light3D()->SetLightType(LIGHT_TYPE::POINT);
	//pObject->Light3D()->SetLightColor(Vec3(0.5f, 0.5f, 1.f));
	//pObject->Light3D()->SetLightAmbient(Vec3(0.f, 0.f, 0.f));
	//pObject->Light3D()->SetSpecularCoefficient(0.3f);
	//pObject->Light3D()->SetRadius(800.f);
	//
	//pLevel->AddObject(0, pObject);


	// SkyBox 추가
	qGameObject* pSkyBox = new qGameObject;
	pSkyBox->SetName(L"SkyBox");

	pSkyBox->AddComponent(new qTransform);
	pSkyBox->AddComponent(new qSkyBox);
	
	pSkyBox->Transform()->SetRelativePos(0.f, 0.f, 0.f);
	pSkyBox->Transform()->SetRelativeScale(1000.f, 1000.f, 1000.f);


	//Ptr<qTexture> pSkyBoxTex = qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\skybox\\SkyWater.dds");
	//pSkyBox->SkyBox()->SetSkyBoxTexture(pSkyBoxTex);
	//pSkyBox->SkyBox()->SetSkyBoxType(CUBE);		


	Ptr<qTexture> pSkyBoxTex = qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\skybox\\Sky02.jpg");
	pSkyBox->SkyBox()->SetSkyBoxTexture(pSkyBoxTex);
	pSkyBox->SkyBox()->SetSkyBoxType(SPHERE);

	pLevel->AddObject(0, pSkyBox);


	Ptr<qTexture> pTex = qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\LandScapeTexture\\gl1_ground_II_albedo.TGA");
	Ptr<qTexture> pNTex = qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\LandScapeTexture\\gl1_ground_II_normal.TGA");


	// 평면 오브젝트
	//qGameObject* pPlane = new qGameObject;
	//pPlane->SetName(L"Plane");
	//pPlane->AddComponent(new qTransform);
	//pPlane->AddComponent(new qMeshRender);
	//
	//pPlane->Transform()->SetRelativePos(0.f, -500.f, 0.f);
	//pPlane->Transform()->SetRelativeScale(4000.f, 4000.f, 1.f);
	//pPlane->Transform()->SetRelativeRotation(XM_PI / 2.f, 0.f, 0.f);
	//
	//pPlane->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	//pPlane->MeshRender()->SetMaterial(pStd3D_DeferredMtrl);
	//
	//
	//
	//pPlane->MeshRender()->GetMaterial()->SetTexParam(TEX_0, pTex);
	//pPlane->MeshRender()->GetMaterial()->SetTexParam(TEX_1, pNTex);
	//pLevel->AddObject(3, pPlane);



	// Player 추가
	//qGameObject* pPlayer = new qGameObject;
	//pPlayer->SetName(L"Player");
	//pPlayer->AddComponent(new qTransform);
	//pPlayer->AddComponent(new qMeshRender);
	//
	//pPlayer->Transform()->SetRelativePos(0.f, 0.f, 0.f);
	//pPlayer->Transform()->SetRelativeScale(500.f, 500.f, 500.f);
	//pPlayer->Transform()->SetRelativeRotation(0.f, 0.f, 0.f);
	//
	//pPlayer->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"SphereMesh"));
	//pPlayer->MeshRender()->SetMaterial(pStd3D_DeferredMtrl, 0);
	//
	//pPlayer->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, pTex);
	//pPlayer->MeshRender()->GetMaterial(0)->SetTexParam(TEX_1, pNTex);
	////pPlayer->MeshRender()->GetMaterial()->SetTexParam(TEXCUBE_0, pSkyBoxTex);
	//
	//pLevel->AddObject(3, pPlayer);


	// Decal Object 추가
	qGameObject* pDecal = new qGameObject;
	pDecal->SetName(L"Decal");
	pDecal->AddComponent(new qTransform);
	pDecal->AddComponent(new qDecal);

	pDecal->Transform()->SetRelativePos(0.f, 0.f, 1000.f);
	pDecal->Transform()->SetRelativeScale(100.f, 100.f, 100.f);

	pDecal->Decal()->SetDecalTexture(qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\MagicCircle.png"));
	pDecal->Decal()->SetEmissiveTexture(qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\MagicCircle.png"));

	pLevel->AddObject(3, pDecal);



	// LandScape 추가
	qGameObject* pLandScape = new qGameObject;
	pLandScape->SetName(L"LandScape");
	pLandScape->AddComponent(new qTransform);
	pLandScape->AddComponent(new qLandScape);

	pLandScape->Transform()->SetRelativePos(0, 0.f, 0.f);
	pLandScape->Transform()->SetRelativeScale(1000.f, 3000.f, 1000.f);

	pLandScape->LandScape()->SetFace(16, 16);
	//pLandScape->LandScape()->SetHeightMap(qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\HeightMap_01.jpg"));
	pLandScape->LandScape()->CreateHeightMap(1024, 1024);

	pLevel->AddObject(3, pLandScape);


// ============
// FBX Loading
// ============	
	//{
	//	Ptr<qMeshData> pMeshData = nullptr;
	//	qGameObject* pObj = nullptr;
	//
	//	pMeshData = qAssetMgr::GetInst()->LoadFBX(L"fbx\\house.fbx");
	//	pMeshData = qAssetMgr::GetInst()->FindAsset<qMeshData>(L"meshdata\\house.mdat");
	//	pObj = pMeshData->Instantiate();
	//	pObj->SetName(L"House");
	//
	//	pObj->Transform()->SetRelativePos(Vec3(0.f, 150.f, 100.f));
	//	pObj->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
	//
	//	pLevel->AddObject(0, pObj);
	//}

	{
		Ptr<qMeshData> pMeshData = nullptr;
		qGameObject* pObj = nullptr;

		//pMeshData = qAssetMgr::GetInst()->LoadFBX(L"fbx\\Monster.fbx");
		pMeshData = qAssetMgr::GetInst()->FindAsset<qMeshData>(L"meshdata\\Monster.mdat");
		pObj = pMeshData->Instantiate();
		pObj->SetName(L"Monster");
		pObj->GetRenderComponent()->SetFrustumCheck(false);

		pObj->Transform()->SetRelativePos(Vec3(200.f, 0.f, 200.f));
		pObj->Transform()->SetRelativeScale(Vec3(5.f, 5.f, 5.f));
		pObj->Transform()->SetRelativeRotation(0.f, XM_PI / 2.f, 0.f);

		pLevel->AddObject(0, pObj);
	}


	// 충돌 지정
	qCollisionMgr::GetInst()->CollisionCheck(3, 4);		// Player vs Monster
	qCollisionMgr::GetInst()->CollisionCheck(5, 4);		// Player Projectile vs Monster

	ChangeLevel(pLevel, LEVEL_STATE::STOP);


}

void qTestLevel::CreatePrefab()
{
	//qGameObject* pProto = new qGameObject;
	//pProto->SetName(L"Missile");
	//pProto->AddComponent(new qTransform);
	//pProto->AddComponent(new qMeshRender);
	//pProto->AddComponent(new qMissileScript);
	//
	//pProto->Transform()->SetRelativeScale(100.f, 100.f, 1.f);
	//
	//pProto->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	//pProto->MeshRender()->SetMaterial(qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl"));
	//
	//Ptr<qPrefab> pPrefab = new qPrefab;
	//pPrefab->SetProtoObject(pProto);
	//
	//qAssetMgr::GetInst()->AddAsset<qPrefab>(L"MissilePref", pPrefab);
	//
	//wstring FilePath = qPathMgr::GetInst()->GetContentPath();
	//FilePath += L"prefab\\Missile.pref";
	//pPrefab->Save(FilePath);
}
