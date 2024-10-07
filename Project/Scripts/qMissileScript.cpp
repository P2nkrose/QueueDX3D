#include "pch.h"
#include "qMissileScript.h"

qMissileScript::qMissileScript()
	: qScript(UINT(SCRIPT_TYPE::MISSILESCRIPT))
	, m_Speed(1000.f)
{
}

qMissileScript::~qMissileScript()
{
	
}

void qMissileScript::Begin()
{
	GetRenderComponent()->GetDynamicMaterial();

	Ptr<qMaterial> pMtrl = GetRenderComponent()->GetMaterial();
	
	if (nullptr != pMtrl)
	{
		Ptr<qTexture> pTexture = qAssetMgr::GetInst()->Load<qTexture>(L"texture\\missile.png", L"texture\\missile.png");
		pMtrl->SetTexParam(TEX_0, pTexture);
	}
}

void qMissileScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	vPos.y += DT * m_Speed;

	Transform()->SetRelativePos(vPos);
}

void qMissileScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	DeleteObject(_OtherObject);
}



void qMissileScript::SaveToFile(FILE* _File)
{
	fwrite(&m_Speed, 4, 1, _File);
}

void qMissileScript::LoadFromFile(FILE* _File)
{
	fread(&m_Speed, 4, 1, _File);
}
