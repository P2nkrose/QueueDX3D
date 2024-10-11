#include "pch.h"
#include "qLight3D.h"

#include "qRenderMgr.h"
#include "qTransform.h"

qLight3D::qLight3D()
	: qComponent(COMPONENT_TYPE::LIGHT3D)
{
}

qLight3D::~qLight3D()
{
}

void qLight3D::SetLightType(LIGHT_TYPE _Type)
{
	m_Info.Type = _Type;
}


void qLight3D::FinalTick()
{
	m_Info.WorldPos = Transform()->GetWorldPos();
	m_Info.WorldDir = Transform()->GetWorldDir(DIR::FRONT);

	// 자신을 Render Manager 에 등록시킴
	qRenderMgr::GetInst()->RegisterLight3D(this);
}

void qLight3D::SaveToFile(FILE* _File)
{
	fwrite(&m_Info, sizeof(tLightInfo), 1, _File);
}

void qLight3D::LoadFromFile(FILE* _File)
{
	fread(&m_Info, sizeof(tLightInfo), 1, _File);
}

