#include "pch.h"
#include "qDecal.h"

#include "qAssetMgr.h"
#include "qTransform.h"

qDecal::qDecal()
	: qRenderComponent(COMPONENT_TYPE::DECAL)
{
	SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"CubeMesh"));
	SetMaterial(qAssetMgr::GetInst()->FindAsset<qMaterial>(L"DecalMtrl"));
}

qDecal::~qDecal()
{
}

void qDecal::FinalTick()
{
	//Vec3 vStart = Transform()->GetWorldPos();
	//Vec3 vEnd = vStart + Vec3(0.f, 10000.f, 0.f);

	//DrawDebugLine(vStart, vEnd, Vec4(0.f, 1.f, 0.f, 1.f), 0.f, true);

	DrawDebugCube(Transform()->GetWorldMat(), Vec4(0.f, 1.f, 0.f, 1.f), 0, true);
}

void qDecal::Render()
{
	Transform()->Binding();

	GetMaterial()->SetTexParam(TEX_1, m_DecalTex);
	GetMaterial()->SetTexParam(TEX_2, m_EmissiveTex);
	GetMaterial()->Binding();

	GetMesh()->Render();
}

void qDecal::SaveToFile(FILE* _File)
{
}

void qDecal::LoadFromFile(FILE* _File)
{
}
