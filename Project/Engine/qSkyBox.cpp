#include "pch.h"
#include "qSkyBox.h"

#include "qTransform.h"
#include "qAssetMgr.h"

qSkyBox::qSkyBox()
	: qRenderComponent(COMPONENT_TYPE::SKYBOX)
{
	SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"SphereMesh"));
	SetMaterial(qAssetMgr::GetInst()->FindAsset<qMaterial>(L"SkyBoxMtrl"));
}

qSkyBox::~qSkyBox()
{
}

void qSkyBox::FinalTick()
{
	// 1. 시점 카메라 의 최대 시야거리로, Transform 의 Scale 을 설정한다.
	//  - Play -> Main Cam
	//  - Pause, Stop -> Editor Cam

	// 2. SkyBox 위치를 시점 카메라 위치로 옮긴다.
}

void qSkyBox::Render()
{
	Transform()->Binding();

	GetMaterial()->Binding();

	GetMesh()->Render();
}

void qSkyBox::SaveToFile(FILE* _File)
{
}

void qSkyBox::LoadFromFile(FILE* _File)
{
}
