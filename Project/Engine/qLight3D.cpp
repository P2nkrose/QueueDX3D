#include "pch.h"
#include "qLight3D.h"

#include "qRenderMgr.h"
#include "qTransform.h"

#include "qAssetMgr.h"

qLight3D::qLight3D()
	: qComponent(COMPONENT_TYPE::LIGHT3D)
	, m_Info{}
	, m_LightIdx(-1)
{
	SetLightType(LIGHT_TYPE::DIRECTIONAL);
}

qLight3D::~qLight3D()
{
}

void qLight3D::SetLightType(LIGHT_TYPE _Type)
{
	m_Info.Type = _Type;

	if (m_Info.Type == LIGHT_TYPE::DIRECTIONAL)
	{
		m_VolumeMesh = qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh");
		m_LightMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"DirLightMtrl");
	}

	else if (m_Info.Type == LIGHT_TYPE::POINT)
	{
		m_VolumeMesh = qAssetMgr::GetInst()->FindAsset<qMesh>(L"SphereMesh");
		m_LightMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"PointLightMtrl");
	}

	else if (m_Info.Type == LIGHT_TYPE::SPOT)
	{
		m_VolumeMesh = qAssetMgr::GetInst()->FindAsset<qMesh>(L"ConeMesh");
		m_LightMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"SpotLightMtrl");
	}
}


void qLight3D::FinalTick()
{
	m_Info.WorldPos = Transform()->GetWorldPos();
	m_Info.WorldDir = Transform()->GetWorldDir(DIR::FRONT);

	// 자신을 Render Manager 에 등록시킴
	m_LightIdx = qRenderMgr::GetInst()->RegisterLight3D(this);
}

void qLight3D::Render()
{
	m_LightMtrl->SetScalarParam(INT_0, m_LightIdx);
	m_LightMtrl->SetTexParam(TEX_0, qAssetMgr::GetInst()->FindAsset<qTexture>(L"PositionTargetTex"));
	m_LightMtrl->SetTexParam(TEX_1, qAssetMgr::GetInst()->FindAsset<qTexture>(L"NormalTargetTex"));
	m_LightMtrl->Binding();
	m_VolumeMesh->Render();
}


void qLight3D::SaveToFile(FILE* _File)
{
	fwrite(&m_Info, sizeof(tLightInfo), 1, _File);
}

void qLight3D::LoadFromFile(FILE* _File)
{
	fread(&m_Info, sizeof(tLightInfo), 1, _File);
}



