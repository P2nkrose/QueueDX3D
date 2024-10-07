#include "pch.h"
#include "qLight2D.h"

#include "qTransform.h"
#include "qRenderMgr.h"

qLight2D::qLight2D()
	: qComponent(COMPONENT_TYPE::LIGHT2D)
	, m_Info{}
{
}

qLight2D::~qLight2D()
{
}

void qLight2D::FinalTick()
{
	m_Info.WorldPos = Transform()->GetWorldPos();
	m_Info.WorldDir = Transform()->GetWorldDir(DIR::RIGHT);

	// 자신을 RenderMgr에 등록시킴
	qRenderMgr::GetInst()->RegisterLight2D(this);
}


void qLight2D::SetLightType(LIGHT_TYPE _Type)
{
	m_Info.Type = _Type;
}


void qLight2D::SaveToFile(FILE* _File)
{
	fwrite(&m_Info, sizeof(tLightInfo), 1, _File);
}

void qLight2D::LoadFromFile(FILE* _File)
{
	fread(&m_Info, sizeof(tLightInfo), 1, _File);
}
