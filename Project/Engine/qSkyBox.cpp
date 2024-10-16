#include "pch.h"
#include "qSkyBox.h"

#include "qTransform.h"
#include "qAssetMgr.h"

qSkyBox::qSkyBox()
	: qRenderComponent(COMPONENT_TYPE::SKYBOX)
	, m_Type(SPHERE)
{
	SetSkyBoxType(m_Type);
}

qSkyBox::~qSkyBox()
{
}


void qSkyBox::SetSkyBoxType(SKYBOX_TYPE _Type)
{
	m_Type = _Type;

	if (SKYBOX_TYPE::SPHERE == m_Type)
		SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"SphereMesh"));
	else if (SKYBOX_TYPE::CUBE == m_Type)
		SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"CubeMesh"));

	// Mesh 가 변경되면 재질을 다시 설정해야 한다.
	SetMaterial(qAssetMgr::GetInst()->FindAsset<qMaterial>(L"SkyBoxMtrl"));
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

	GetMaterial()->SetScalarParam(INT_0, (int)m_Type);

	if (m_Type == SPHERE)
	{
		if (!m_SkyBoxTex->IsCubeMap())
			GetMaterial()->SetTexParam(TEX_0, m_SkyBoxTex);
		else
			GetMaterial()->SetTexParam(TEX_0, nullptr);
	}

	else if (m_Type == CUBE)
	{
		if (m_SkyBoxTex->IsCubeMap())
			GetMaterial()->SetTexParam(TEXCUBE_0, m_SkyBoxTex);
		else
			GetMaterial()->SetTexParam(TEXCUBE_0, nullptr);
	}

	GetMaterial()->Binding();
	GetMesh()->Render();
}

void qSkyBox::SaveToFile(FILE* _File)
{
}

void qSkyBox::LoadFromFile(FILE* _File)
{
}

