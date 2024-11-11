#include "pch.h"
#include "qLandScape.h"

#include "qAssetMgr.h"

#include "qTransform.h"

qLandScape::qLandScape()
	: qRenderComponent(COMPONENT_TYPE::LANDSCAPE)
	, m_FaceX(1)
	, m_FaceZ(1)
	, m_TessLevel(8.f)
{
	SetFace(m_FaceX, m_FaceZ);
}

qLandScape::~qLandScape()
{
}

void qLandScape::FinalTick()
{
}

void qLandScape::Render()
{
	Transform()->Binding();

	GetMaterial()->GetShader()->SetRSType(RS_TYPE::WIRE_FRAME);

	// 지형의 면 개수
	GetMaterial()->SetScalarParam(INT_0, m_FaceX);
	GetMaterial()->SetScalarParam(INT_1, m_FaceZ);
	GetMaterial()->SetScalarParam(FLOAT_0, m_TessLevel);

	// 지형에 적용시킬 높이맵
	GetMaterial()->SetTexParam(TEX_0, m_HeightMap);

	// 재질 바인딩
	GetMaterial()->Binding();

	// 렌더링
	GetMesh()->Render();
}

void qLandScape::SetFace(int _X, int _Z)
{
	m_FaceX = _X;
	m_FaceZ = _Z;

	CreateMesh();
	SetMaterial(qAssetMgr::GetInst()->FindAsset<qMaterial>(L"LandScapeMtrl"));
}

void qLandScape::CreateMesh()
{
	Vtx v;
	vector<Vtx> vecVtx;

	// 정점
	for (UINT Row = 0; Row < m_FaceZ + 1; ++Row)
	{
		for (UINT Col = 0; Col < m_FaceX + 1; ++Col)
		{
			v.vPos = Vec3((float)Col, 0.f, (float)Row);
			v.vNormal = Vec3(0.f, 1.f, 0.f);
			v.vTangent = Vec3(1.f, 0.f, 0.f);
			v.vBinormal = Vec3(0.f, 0.f, -1.f);

			vecVtx.push_back(v);
		}
	}

	// 인덱스
	vector<UINT> vecIdx;
	for (UINT Row = 0; Row < m_FaceZ; ++Row)
	{
		for (UINT Col = 0; Col < m_FaceX; ++Col)
		{
			// 0
			// | \
			// 2--1
			vecIdx.push_back((Row * (m_FaceX + 1)) + Col + m_FaceX + 1);
			vecIdx.push_back((Row * (m_FaceX + 1)) + Col + 1);
			vecIdx.push_back((Row * (m_FaceX + 1)) + Col);

			// 1--2 
			//  \ |
			//    0
			vecIdx.push_back((Row * (m_FaceX + 1)) + Col + m_FaceX + 1);
			vecIdx.push_back((Row * (m_FaceX + 1)) + Col + m_FaceX + 1 + 1);
			vecIdx.push_back((Row * (m_FaceX + 1)) + Col + 1);
		}
	}

	Ptr<qMesh> pMesh = new qMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	SetMesh(pMesh);
}

void qLandScape::SaveToFile(FILE* _File)
{
}

void qLandScape::LoadFromFile(FILE* _File)
{
}


