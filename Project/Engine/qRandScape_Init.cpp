#include "pch.h"
#include "qLandScape.h"

#include "qAssetMgr.h"
#include "qTexture.h"

#include "qDevice.h"
#include "qStructuredBuffer.h"

void qLandScape::Init()
{
	// LandScape 전용 Mesh 생성
	CreateMesh();

	// LandScape 전용 재질 참조
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"LandScapeMtrl");
	SetMaterial(pMtrl);

	// LandScape 전용 컴퓨트 쉐이더 제작
	CreateComputeShader();

	// LandScape 용 텍스쳐 생성 및 로딩
	CreateTextureAndStructuredBuffer();

	// BrushTexture 추가	
	AddBrushTexture(qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\brush\\TX_GlowScene_2.png"));
	AddBrushTexture(qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\brush\\TX_HitFlash_0.png"));
	AddBrushTexture(qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\brush\\TX_HitFlash02.png"));
	AddBrushTexture(qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\brush\\TX_Twirl02.png"));
	AddBrushTexture(qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\brush\\FX_Flare.png"));
	m_BrushIdx = 0;
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
			vecIdx.push_back((Row * (m_FaceX + 1)) + Col + 1);
			vecIdx.push_back((Row * (m_FaceX + 1)) + Col + m_FaceX + 1);
			vecIdx.push_back((Row * (m_FaceX + 1)) + Col + m_FaceX + 1 + 1);
		}
	}

	Ptr<qMesh> pMesh = new qMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	SetMesh(pMesh);
}

void qLandScape::CreateComputeShader()
{
	// HeightMapCS 가 있으면 찾아오고 없으면 컴파일해서 등록한다.
	m_HeightMapCS = (qHeightMapCS*)qAssetMgr::GetInst()->FindAsset<qComputeShader>(L"HeightMapCS").Get();
	if (nullptr == m_HeightMapCS)
	{
		m_HeightMapCS = new qHeightMapCS;
		qAssetMgr::GetInst()->AddAsset<qComputeShader>(L"HeightMapCS", m_HeightMapCS.Get());
	}

	// RaycastCS 생성
	m_RaycastCS = (qRaycastCS*)qAssetMgr::GetInst()->FindAsset<qComputeShader>(L"RaycastCS").Get();
	if (nullptr == m_RaycastCS)
	{
		m_RaycastCS = new qRaycastCS;
		qAssetMgr::GetInst()->AddAsset<qComputeShader>(L"RaycastCS", m_RaycastCS.Get());
	}
}

void qLandScape::CreateTextureAndStructuredBuffer()
{
	// Raycasting 결과를 받는 용도의 구조화버퍼
	m_RaycastOut = new qStructuredBuffer;
	m_RaycastOut->Create(sizeof(tRaycastOut), 1, SB_TYPE::SRV_UAV, true);
}




void qLandScape::CreateHeightMap(UINT _Width, UINT _Height)
{
	m_IsHeightMapCreated = true;

	m_HeightMap = qAssetMgr::GetInst()->CreateTexture(L"LandScapeHeightMap", _Width, _Height
		, DXGI_FORMAT_R32_FLOAT
		, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
}
