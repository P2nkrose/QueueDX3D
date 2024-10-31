#include "pch.h"
#include "qAssetMgr.h"
#include "qDevice.h"

void qAssetMgr::Init()
{

	CreateEngineMesh();

	CreateEngineTexture();

	CreateEngineSprite();

	CreateEngineGraphicShader();

	CreateEngineComputeShader();

	CreateEngineMaterial();
}

void qAssetMgr::CreateEngineMesh()
{
	Ptr<qMesh> pMesh = nullptr;
	Vtx v;

	// Point Mesh
	pMesh = new qMesh(true);
	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vColor = Vec3(0.f, 0.f, 0.f);
	v.vUV = Vec2(0.f, 0.f);

	UINT i = 0;
	pMesh->Create(&v, 1, &i, 1);
	AddAsset(L"PointMesh", pMesh);

	
	// RectMesh 생성
	// 0 --- 1
	// |  \  |
	// 3 --- 2
	
	
	// Vertex
	Vtx arrVtx[4] = {};
	
	v.vPos = Vec3(-0.5f, 0.5f, 0.f);
	v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	v.vUV = Vec2(0.f, 0.f);
	v.vTangent = Vec3(1.f, 0.f, 0.f);
	v.vNormal = Vec3(0.f, 0.f, -1.f);
	v.vBinormal = Vec3(0.f, -1.f, 0.f);
	arrVtx[0] = v;

	v.vPos = Vec3(0.5f, 0.5f, 0.f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	v.vUV = Vec2(1.f, 0.f);
	arrVtx[1] = v;

	v.vPos = Vec3(0.5f, -0.5f, 0.f);
	v.vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	v.vUV = Vec2(1.f, 1.f);
	arrVtx[2] = v;

	v.vPos = Vec3(-0.5f, -0.5f, 0.f);
	v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	v.vUV = Vec2(0.f, 1.f);
	arrVtx[3] = v;
	
	// Index 버퍼 생성
	UINT arrIdx[6] = {};
	arrIdx[0] = 0;		arrIdx[1] = 1;		arrIdx[2] = 2;
	arrIdx[3] = 0;		arrIdx[4] = 2;		arrIdx[5] = 3;
	
	pMesh = new qMesh(true);
	pMesh->Create(arrVtx, 4, arrIdx, 6);
	pMesh->SetEngineAsset();
	AddAsset(L"RectMesh", pMesh);
	
	// RectMesh_Debug
	arrIdx[0] = 0;	arrIdx[1] = 1;	arrIdx[2] = 2;	arrIdx[3] = 3;	arrIdx[4] = 0;
	
	pMesh = new qMesh(true);
	pMesh->Create(arrVtx, 4, arrIdx, 5);
	pMesh->SetEngineAsset();
	AddAsset(L"RectMesh_Debug", pMesh);
	
	
	// CircleMesh
	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;

	
	int Slice = 40;
	float fTheta = XM_2PI / Slice;
	float Radius = 0.5f;
	
	// 중심점
	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vUV = Vec2(0.5f, 0.5f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	v.vTangent = Vec3(1.f, 0.f, 0.f);
	v.vNormal = Vec3(0.f, 0.f, -1.f);
	v.vBinormal = Vec3(0.f, -1.f, 0.f);
	vecVtx.push_back(v);
	
	// 테두리
	float Angle = 0.f;
	for (int i = 0; i < Slice + 1; ++i)
	{
		v.vPos = Vec3(Radius * cosf(Angle), Radius * sinf(Angle), 0.f);
		v.vUV = Vec2(v.vPos.x + 0.5f, -(v.vPos.y - 0.5f));
		v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
		vecVtx.push_back(v);
	
		Angle += fTheta;
	}
	
	
	// 인덱스
	for (int i = 0; i < Slice; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}
	
	pMesh = new qMesh(true);
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	pMesh->SetEngineAsset();
	AddAsset(L"CircleMesh", pMesh);
	
	
	// CircleMesh_Debug
	vecIdx.clear();
	
	for (size_t i = 0; i < vecVtx.size(); ++i)
	{
		vecIdx.push_back((UINT)i);
	}
	
	pMesh = new qMesh(true);
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	pMesh->SetEngineAsset();
	AddAsset(L"CircleMesh_Debug", pMesh);
	vecIdx.clear();


	// CubeMesh
	// 24개의 정점이 필요
	// 평면 하나당 정점 4개 x 6면 = 24개
	Vtx arrCube[24] = {};

	// 윗면
	arrCube[0].vPos = Vec3(-0.5f, 0.5f, 0.5f);
	arrCube[0].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	arrCube[0].vUV = Vec2(0.f, 0.f);
	arrCube[0].vTangent = Vec3(1.f, 0.f, 0.f);
	arrCube[0].vNormal = Vec3(0.f, 1.f, 0.f);
	arrCube[0].vBinormal = Vec3(0.f, 0.f, -1.f);

	arrCube[1].vPos = Vec3(0.5f, 0.5f, 0.5f);
	arrCube[1].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	arrCube[1].vUV = Vec2(1.f, 0.f);
	arrCube[1].vTangent = Vec3(1.f, 0.f, 0.f);
	arrCube[1].vNormal = Vec3(0.f, 1.f, 0.f);
	arrCube[1].vBinormal = Vec3(0.f, 0.f, -1.f);

	arrCube[2].vPos = Vec3(0.5f, 0.5f, -0.5f);
	arrCube[2].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	arrCube[2].vUV = Vec2(1.f, 1.f);
	arrCube[2].vTangent = Vec3(1.f, 0.f, 0.f);
	arrCube[2].vNormal = Vec3(0.f, 1.f, 0.f);
	arrCube[2].vBinormal = Vec3(0.f, 0.f, -1.f);

	arrCube[3].vPos = Vec3(-0.5f, 0.5f, -0.5f);
	arrCube[3].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	arrCube[3].vUV = Vec2(0.f, 1.f);
	arrCube[3].vTangent = Vec3(1.f, 0.f, 0.f);
	arrCube[3].vNormal = Vec3(0.f, 1.f, 0.f);
	arrCube[3].vBinormal = Vec3(0.f, 0.f, -1.f);


	// 아랫 면	
	arrCube[4].vPos = Vec3(-0.5f, -0.5f, -0.5f);
	arrCube[4].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrCube[4].vUV = Vec2(0.f, 0.f);
	arrCube[4].vTangent = Vec3(1.f, 0.f, 0.f);
	arrCube[4].vNormal = Vec3(0.f, -1.f, 0.f);
	arrCube[4].vBinormal = Vec3(0.f, 0.f, 1.f);

	arrCube[5].vPos = Vec3(0.5f, -0.5f, -0.5f);
	arrCube[5].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrCube[5].vUV = Vec2(1.f, 0.f);
	arrCube[5].vTangent = Vec3(1.f, 0.f, 0.f);
	arrCube[5].vNormal = Vec3(0.f, -1.f, 0.f);
	arrCube[5].vBinormal = Vec3(0.f, 0.f, 1.f);

	arrCube[6].vPos = Vec3(0.5f, -0.5f, 0.5f);
	arrCube[6].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrCube[6].vUV = Vec2(1.f, 1.f);
	arrCube[6].vTangent = Vec3(1.f, 0.f, 0.f);
	arrCube[6].vNormal = Vec3(0.f, -1.f, 0.f);
	arrCube[6].vBinormal = Vec3(0.f, 0.f, 1.f);

	arrCube[7].vPos = Vec3(-0.5f, -0.5f, 0.5f);
	arrCube[7].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrCube[7].vUV = Vec2(0.f, 1.f);
	arrCube[7].vTangent = Vec3(1.f, 0.f, 0.f);
	arrCube[7].vNormal = Vec3(0.f, -1.f, 0.f);
	arrCube[7].vBinormal = Vec3(0.f, 0.f, 1.f);

	// 왼쪽 면
	arrCube[8].vPos = Vec3(-0.5f, 0.5f, 0.5f);
	arrCube[8].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrCube[8].vUV = Vec2(0.f, 0.f);
	arrCube[8].vTangent = Vec3(0.f, 0.f, -1.f);
	arrCube[8].vNormal = Vec3(-1.f, 0.f, 0.f);
	arrCube[8].vBinormal = Vec3(0.f, -1.f, 0.f);

	arrCube[9].vPos = Vec3(-0.5f, 0.5f, -0.5f);
	arrCube[9].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrCube[9].vUV = Vec2(1.f, 0.f);
	arrCube[9].vTangent = Vec3(0.f, 0.f, -1.f);
	arrCube[9].vNormal = Vec3(-1.f, 0.f, 0.f);
	arrCube[9].vBinormal = Vec3(0.f, -1.f, 0.f);

	arrCube[10].vPos = Vec3(-0.5f, -0.5f, -0.5f);
	arrCube[10].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrCube[10].vUV = Vec2(1.f, 1.f);
	arrCube[10].vTangent = Vec3(0.f, 0.f, -1.f);
	arrCube[10].vNormal = Vec3(-1.f, 0.f, 0.f);
	arrCube[10].vBinormal = Vec3(0.f, -1.f, 0.f);

	arrCube[11].vPos = Vec3(-0.5f, -0.5f, 0.5f);
	arrCube[11].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrCube[11].vUV = Vec2(0.f, 1.f);
	arrCube[11].vTangent = Vec3(0.f, 0.f, -1.f);
	arrCube[11].vNormal = Vec3(-1.f, 0.f, 0.f);
	arrCube[11].vBinormal = Vec3(0.f, -1.f, 0.f);

	// 오른쪽 면
	arrCube[12].vPos = Vec3(0.5f, 0.5f, -0.5f);
	arrCube[12].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrCube[12].vUV = Vec2(0.f, 0.f);
	arrCube[12].vTangent = Vec3(0.f, 0.f, 1.f);
	arrCube[12].vNormal = Vec3(1.f, 0.f, 0.f);
	arrCube[12].vBinormal = Vec3(0.f, -1.f, 0.f);

	arrCube[13].vPos = Vec3(0.5f, 0.5f, 0.5f);
	arrCube[13].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrCube[13].vUV = Vec2(1.f, 0.f);
	arrCube[13].vTangent = Vec3(0.f, 0.f, 1.f);
	arrCube[13].vNormal = Vec3(1.f, 0.f, 0.f);
	arrCube[13].vBinormal = Vec3(0.f, -1.f, 0.f);

	arrCube[14].vPos = Vec3(0.5f, -0.5f, 0.5f);
	arrCube[14].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrCube[14].vUV = Vec2(1.f, 1.f);
	arrCube[14].vTangent = Vec3(0.f, 0.f, 1.f);
	arrCube[14].vNormal = Vec3(1.f, 0.f, 0.f);
	arrCube[14].vBinormal = Vec3(0.f, -1.f, 0.f);

	arrCube[15].vPos = Vec3(0.5f, -0.5f, -0.5f);
	arrCube[15].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrCube[15].vUV = Vec2(0.f, 1.f);
	arrCube[15].vTangent = Vec3(0.f, 0.f, 1.f);
	arrCube[15].vNormal = Vec3(1.f, 0.f, 0.f);
	arrCube[15].vBinormal = Vec3(0.f, -1.f, 0.f);

	// 뒷 면
	arrCube[16].vPos = Vec3(0.5f, 0.5f, 0.5f);
	arrCube[16].vColor = Vec4(1.f, 1.f, 0.f, 1.f);
	arrCube[16].vUV = Vec2(0.f, 0.f);
	arrCube[16].vTangent = Vec3(-1.f, 0.f, 0.f);
	arrCube[16].vNormal = Vec3(0.f, 0.f, 1.f);
	arrCube[16].vBinormal = Vec3(0.f, -1.f, 1.f);

	arrCube[17].vPos = Vec3(-0.5f, 0.5f, 0.5f);
	arrCube[17].vColor = Vec4(1.f, 1.f, 0.f, 1.f);
	arrCube[17].vUV = Vec2(1.f, 0.f);
	arrCube[17].vTangent = Vec3(-1.f, 0.f, 0.f);
	arrCube[17].vNormal = Vec3(0.f, 0.f, 1.f);
	arrCube[17].vBinormal = Vec3(0.f, -1.f, 1.f);

	arrCube[18].vPos = Vec3(-0.5f, -0.5f, 0.5f);
	arrCube[18].vColor = Vec4(1.f, 1.f, 0.f, 1.f);
	arrCube[18].vUV = Vec2(1.f, 1.f);
	arrCube[18].vTangent = Vec3(-1.f, 0.f, 0.f);
	arrCube[18].vNormal = Vec3(0.f, 0.f, 1.f);
	arrCube[18].vBinormal = Vec3(0.f, -1.f, 1.f);

	arrCube[19].vPos = Vec3(0.5f, -0.5f, 0.5f);
	arrCube[19].vColor = Vec4(1.f, 1.f, 0.f, 1.f);
	arrCube[19].vUV = Vec2(0.f, 1.f);
	arrCube[19].vTangent = Vec3(-1.f, 0.f, 0.f);
	arrCube[19].vNormal = Vec3(0.f, 0.f, 1.f);
	arrCube[19].vBinormal = Vec3(0.f, -1.f, 1.f);

	// 앞 면
	arrCube[20].vPos = Vec3(-0.5f, 0.5f, -0.5f);
	arrCube[20].vColor = Vec4(1.f, 0.f, 1.f, 1.f);
	arrCube[20].vUV = Vec2(0.f, 0.f);
	arrCube[20].vTangent = Vec3(1.f, 0.f, 0.f);
	arrCube[20].vNormal = Vec3(0.f, 0.f, -1.f);
	arrCube[20].vBinormal = Vec3(0.f, -1.f, 0.f);

	arrCube[21].vPos = Vec3(0.5f, 0.5f, -0.5f);
	arrCube[21].vColor = Vec4(1.f, 0.f, 1.f, 1.f);
	arrCube[21].vUV = Vec2(1.f, 0.f);
	arrCube[21].vTangent = Vec3(1.f, 0.f, 0.f);
	arrCube[21].vNormal = Vec3(0.f, 0.f, -1.f);
	arrCube[21].vBinormal = Vec3(0.f, -1.f, 0.f);

	arrCube[22].vPos = Vec3(0.5f, -0.5f, -0.5f);
	arrCube[22].vColor = Vec4(1.f, 0.f, 1.f, 1.f);
	arrCube[22].vUV = Vec2(1.f, 1.f);
	arrCube[22].vTangent = Vec3(1.f, 0.f, 0.f);
	arrCube[22].vNormal = Vec3(0.f, 0.f, -1.f);
	arrCube[22].vBinormal = Vec3(0.f, -1.f, 0.f);

	arrCube[23].vPos = Vec3(-0.5f, -0.5f, -0.5f);
	arrCube[23].vColor = Vec4(1.f, 0.f, 1.f, 1.f);
	arrCube[23].vUV = Vec2(0.f, 1.f);
	arrCube[23].vTangent = Vec3(1.f, 0.f, 0.f);
	arrCube[23].vNormal = Vec3(0.f, 0.f, -1.f);
	arrCube[23].vBinormal = Vec3(0.f, -1.f, 0.f);

	// 인덱스
	for (int i = 0; i < 12; i += 2)
	{
		vecIdx.push_back(i * 2);
		vecIdx.push_back(i * 2 + 1);
		vecIdx.push_back(i * 2 + 2);

		vecIdx.push_back(i * 2);
		vecIdx.push_back(i * 2 + 2);
		vecIdx.push_back(i * 2 + 3);
	}

	pMesh = new qMesh(true);
	pMesh->Create(arrCube, 24, vecIdx.data(), (UINT)vecIdx.size());
	AddAsset(L"CubeMesh", pMesh);
	
	vecIdx.clear();

	// CubeMesh_Debug
	vecIdx.push_back(0); vecIdx.push_back(1); vecIdx.push_back(2); vecIdx.push_back(3); vecIdx.push_back(4);
	vecIdx.push_back(7); vecIdx.push_back(6); vecIdx.push_back(5); vecIdx.push_back(4); vecIdx.push_back(3);
	vecIdx.push_back(0); vecIdx.push_back(7); vecIdx.push_back(6); vecIdx.push_back(1); vecIdx.push_back(2);
	vecIdx.push_back(5);

	pMesh = new qMesh(true);
	pMesh->Create(arrCube, 24, vecIdx.data(), (UINT)vecIdx.size());
	AddAsset(L"CubeMesh_Debug", pMesh);

	vecVtx.clear();
	vecIdx.clear();


	// ============
	// Sphere Mesh
	// ============
	float fRadius = 0.5f;

	// Top
	v.vPos = Vec3(0.f, fRadius, 0.f);
	v.vUV = Vec2(0.5f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	v.vNormal = v.vPos;
	v.vNormal.Normalize();
	v.vTangent = Vec3(1.f, 0.f, 0.f);
	v.vBinormal = Vec3(0.f, 0.f, -1.f);
	vecVtx.push_back(v);

	// Body
	UINT iStackCount = 40; // 가로 분할 개수
	UINT iSliceCount = 40; // 세로 분할 개수

	float fStackAngle = XM_PI / iStackCount;
	float fSliceAngle = XM_2PI / iSliceCount;

	float fUVXStep = 1.f / (float)iSliceCount;
	float fUVYStep = 1.f / (float)iStackCount;

	for (UINT i = 1; i < iStackCount; ++i)
	{
		float phi = i * fStackAngle;

		for (UINT j = 0; j <= iSliceCount; ++j)
		{
			float theta = j * fSliceAngle;

			v.vPos = Vec3(fRadius * sinf(i * fStackAngle) * cosf(j * fSliceAngle)
				, fRadius * cosf(i * fStackAngle)
				, fRadius * sinf(i * fStackAngle) * sinf(j * fSliceAngle));

			v.vUV = Vec2(fUVXStep * j, fUVYStep * i);
			v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
			v.vNormal = v.vPos;
			v.vNormal.Normalize();

			v.vTangent.x = -fRadius * sinf(phi) * sinf(theta);
			v.vTangent.y = 0.f;
			v.vTangent.z = fRadius * sinf(phi) * cosf(theta);
			v.vTangent.Normalize();

			v.vNormal.Cross(v.vTangent, v.vBinormal);
			v.vBinormal.Normalize();

			vecVtx.push_back(v);
		}
	}

	// Bottom
	v.vPos = Vec3(0.f, -fRadius, 0.f);
	v.vUV = Vec2(0.5f, 1.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	v.vNormal = v.vPos;
	v.vNormal.Normalize();

	v.vTangent = Vec3(1.f, 0.f, 0.f);
	v.vBinormal = Vec3(0.f, 0.f, -1.f);
	vecVtx.push_back(v);

	// 인덱스
	// 북극점
	for (UINT i = 0; i < iSliceCount; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}

	// 몸통
	for (UINT i = 0; i < iStackCount - 2; ++i)
	{
		for (UINT j = 0; j < iSliceCount; ++j)
		{
			// + 
			// | \
			// +--+
			vecIdx.push_back((iSliceCount + 1) * (i)+(j)+1);
			vecIdx.push_back((iSliceCount + 1) * (i + 1) + (j + 1) + 1);
			vecIdx.push_back((iSliceCount + 1) * (i + 1) + (j)+1);

			// +--+
			//  \ |
			//    +
			vecIdx.push_back((iSliceCount + 1) * (i)+(j)+1);
			vecIdx.push_back((iSliceCount + 1) * (i)+(j + 1) + 1);
			vecIdx.push_back((iSliceCount + 1) * (i + 1) + (j + 1) + 1);
		}
	}

	// 남극점
	UINT iBottomIdx = (UINT)vecVtx.size() - 1;
	for (UINT i = 0; i < iSliceCount; ++i)
	{
		vecIdx.push_back(iBottomIdx);
		vecIdx.push_back(iBottomIdx - (i + 2));
		vecIdx.push_back(iBottomIdx - (i + 1));
	}

	pMesh = new qMesh(true);
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset(L"SphereMesh", pMesh);
	vecVtx.clear();
	vecIdx.clear();

}

void qAssetMgr::CreateEngineTexture()
{
	// Post Process 용도 텍스처 생성
	Vec2 Resolution = qDevice::GetInst()->GetResolution();
	Ptr<qTexture> pPostProcessTex = CreateTexture(L"PostProcessTex", (UINT)Resolution.x, (UINT)Resolution.y
				, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE);


	Ptr<qTexture> pEffectTarget = CreateTexture(
		L"EffectTargetTex"
		, (UINT)(Resolution.x), (UINT)(Resolution.y)
		, DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE);

	Ptr<qTexture> pEffectDepth = CreateTexture(
		L"EffectDepthStencilTex"
		, (UINT)(Resolution.x), (UINT)(Resolution.y)
		, DXGI_FORMAT_D24_UNORM_S8_UINT, D3D11_BIND_DEPTH_STENCIL);

	Ptr<qTexture> pEffectBlurTarget = CreateTexture(
		L"EffectBlurTargetTex"
		, (UINT)(Resolution.x), (UINT)(Resolution.y)
		, DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE);



	// Noise Texture 를 미리 만들어놓기
	Load<qTexture>(L"texture\\noise\\noise_01.png", L"texture\\noise\\noise_01.png");
	Load<qTexture>(L"texture\\noise\\noise_02.png", L"texture\\noise\\noise_02.png");
	Load<qTexture>(L"texture\\noise\\noise_03.jpg", L"texture\\noise\\noise_03.jpg");
	Load<qTexture>(L"texture\\noise\\noise_04.jpg", L"texture\\noise\\noise_04.jpg");
	Load<qTexture>(L"texture\\noise\\noise_05.jpg", L"texture\\noise\\noise_05.jpg");
}

void qAssetMgr::CreateEngineSprite()
{
	//wstring strContentPath = qPathMgr::GetInst()->GetContentPath();

	//Ptr<qFlipBook> pFlipBook = new qFlipBook;
	//Load<qFlipBook>(L"Link_MoveDown", L"Animation\\Link_MoveDown.flip");
	//AddAsset(L"Link_MoveDown", pFlipBook);

	//Ptr<qFlipBook> pFlipBook = new qFlipBook;
	//Load<qFlipBook>(L"Link_MoveDown", strContentPath + L"Animation\\" + L"Link_MoveDown" + L".flip");


	//Ptr<qTexture> pTexture = new qTexture;
	//pTexture = Load<qTexture>(L"Link_MoveDownTexture", L"texture\\link.png");
	//Ptr<qSprite> pSprite = nullptr;
	
	//for (int i = 0; i < 10; ++i)
	//{
	//	wchar_t Buffer[50] = {};
	//	swprintf_s(Buffer, 50, L"Link_MoveDown_%d", i);
	//
	//	pSprite = new qSprite;
	//	pSprite = Load<qSprite>(Buffer, wstring(L"Animation\\") + Buffer + L".sprite");		
	//
	//
	//	pSprite->Create(pTexture, Vec2(float(i) * 120.f, 520.f), Vec2(120.f, 130.f));
	//	pSprite->SetRelativePath(wstring(L"Animation\\") + Buffer + L".sprite");
	//	pSprite->SetBackground(Vec2(150.f, 150.f));
	//	AddAsset(Buffer, pSprite);
	//	pSprite->Save(strContentPath + L"Animation\\" + Buffer + L".sprite");
	//}
	//
	//
	//Ptr<qFlipBook> pFilpBook = new qFlipBook;
	//
	//for (int i = 0; i < 10; ++i)
	//{
	//	wchar_t Buffer[50] = {};
	//	swprintf_s(Buffer, 50, L"Link_MoveDown_%d", i);
	//	pFilpBook->AddSprite(FindAsset<qSprite>(Buffer));		
	//}
	//
	//AddAsset(L"Link_MoveDown", pFilpBook);
	//pFilpBook->Save(strContentPath + L"Animation\\" + L"Link_MoveDown" + L".flip");


	
}

void qAssetMgr::CreateEngineGraphicShader()
{
	Ptr<qGraphicShader> pShader = nullptr;

	// Std2DShader
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::DEFAULT);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASKED);

	//pShader->AddScalarParam(INT_0, "Test Parameter");
	pShader->AddTexParam(TEX_0, "OutputTexture");

	AddAsset(L"Std2DShader", pShader);


	// Std2DAlphaBlend
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D_Alphablend");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::ALPHABLEND);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_TRANSPARENT);

	AddAsset(L"Std2DAlphaBlendShader", pShader);


	// EffectShader
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Effect");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::ALPHABLEND);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_EFFECT);

	AddAsset(L"EffectShader", pShader);



	// Std2D UI Shader
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D_UI");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::DEFAULT);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_UI);

	AddAsset(L"Std2DUIShader", pShader);


	// Std2D UI Shader
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D_BOSSUI");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::DEFAULT);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_UI);

	AddAsset(L"Std2DBOSSUIShader", pShader);




	// Std2D HUD Shader
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D_HUD");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::DEFAULT);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_UI);

	AddAsset(L"Std2DHUDShader", pShader);


	// Std2D HUD Shader
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D_BOSSHUD");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::DEFAULT);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_UI);

	AddAsset(L"Std2DBOSSHUDShader", pShader);



	// DebugShapeShader
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\debug.fx", "VS_DebugShape");
	pShader->CreatePixelShader(L"shader\\debug.fx", "PS_DebugShape");

	pShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::ALPHABLEND);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_DEBUG);

	AddAsset(L"DebugShapeShader", pShader);


	// DebugLineShader
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\debug.fx", "VS_DebugLine");
	pShader->CreateGeometryShader(L"shader\\debug.fx", "GS_DebugLine");
	pShader->CreatePixelShader(L"shader\\debug.fx", "PS_DebugLine");

	pShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::ALPHABLEND);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_DEBUG);

	AddAsset(L"DebugLineShader", pShader);

	
	// TileMapShader
	pShader = new qGraphicShader;

	pShader->CreateVertexShader(L"shader\\tilemap.fx", "VS_TileMap");
	pShader->CreatePixelShader(L"shader\\tilemap.fx", "PS_TileMap");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::DEFAULT);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASKED);

	AddAsset(L"TileMapShader", pShader);


	// Particle Shader
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\particle.fx", "VS_Particle");
	pShader->CreateGeometryShader(L"shader\\particle.fx", "GS_Particle");
	pShader->CreatePixelShader(L"shader\\particle.fx", "PS_Particle");

	pShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_WRITE);
	pShader->SetBSType(BS_TYPE::ALPHABLEND);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_PARTICLE);
	AddAsset(L"ParticleRenderShader", pShader);




	// GrayFilterShader
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\postprocess.fx", "VS_GrayFilter");
	pShader->CreatePixelShader(L"shader\\postprocess.fx", "PS_GrayFilter");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetBSType(BS_TYPE::DEFAULT);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_POSTPROCESS);
	AddAsset(L"GrayFilterShader", pShader);


	// DistortionShader
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\postprocess.fx", "VS_Distortion");
	pShader->CreatePixelShader(L"shader\\postprocess.fx", "PS_Distortion");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetBSType(BS_TYPE::DEFAULT);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_POSTPROCESS);
	AddAsset(L"DistortionShader", pShader);


	// BlurShader
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\postprocess.fx", "VS_Blur");
	pShader->CreatePixelShader(L"shader\\postprocess.fx", "PS_Blur");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetBSType(BS_TYPE::ALPHABLEND);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_POSTPROCESS);
	AddAsset(L"BlurShader", pShader);
	
	// EffectMerge
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\postprocess.fx", "VS_EffectMerge");
	pShader->CreatePixelShader(L"shader\\postprocess.fx", "PS_EffectMerge");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetBSType(BS_TYPE::ALPHABLEND);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_POSTPROCESS);
	AddAsset(L"EffectMergeShader", pShader);


	// Std3DShader
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\std3d.fx", "VS_Std3D");
	pShader->CreatePixelShader(L"shader\\std3d.fx", "PS_Std3D");
	pShader->SetRSType(RS_TYPE::CULL_BACK);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::DEFAULT);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_OPAQUE);
	pShader->AddTexParam(TEX_0, "Albedo Texture");
	pShader->AddTexParam(TEX_1, "Normal Texture");
	AddAsset(L"Std3DShader", pShader);


	// Std3D_DeferredShader
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\std3d_deferred.fx", "VS_Std3D_Deferred");
	pShader->CreatePixelShader(L"shader\\std3d_deferred.fx", "PS_Std3D_Deferred");
	pShader->SetRSType(RS_TYPE::CULL_BACK);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::DEFAULT);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_DEFERRED);
	pShader->AddTexParam(TEX_0, "Albedo Texture");
	pShader->AddTexParam(TEX_1, "Normal Texture");
	AddAsset(L"Std3D_DeferredShader", pShader);


	// SkyBoxShader
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\skybox.fx", "VS_SkyBox");
	pShader->CreatePixelShader(L"shader\\skybox.fx", "PS_SkyBox");
	pShader->SetRSType(RS_TYPE::CULL_FRONT);
	pShader->SetDSType(DS_TYPE::LESS_EQUAL);
	pShader->SetBSType(BS_TYPE::DEFAULT);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_OPAQUE);

	pShader->AddTexParam(TEX_0, "Albedo Texture");

	AddAsset(L"SkyBoxShader", pShader);


	// DecalShader
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\decal.fx", "VS_Decal");
	pShader->CreatePixelShader(L"shader\\decal.fx", "PS_Decal");
	pShader->SetRSType(RS_TYPE::CULL_FRONT);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetBSType(BS_TYPE::DECAL);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_DECAL);

	pShader->AddTexParam(TEX_0, "Decal Texture");

	AddAsset(L"DecalShader", pShader);


	// DirLightShadowMap Shader
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\shadowmap.fx", "VS_DirLightShadowMap");
	pShader->CreatePixelShader(L"shader\\shadowmap.fx", "PS_DirLightShadowMap");
	pShader->SetRSType(RS_TYPE::CULL_BACK);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::DEFAULT);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_SHADOWMAP);
	AddAsset(L"DirLightShadowMap", pShader);
}

#include "qParticleTickCS.h"

void qAssetMgr::CreateEngineComputeShader()
{
	// ParticleTick
	Ptr<qComputeShader> pCS = nullptr;

	pCS = new qParticleTickCS;
	AddAsset<qComputeShader>(L"ParticleTickCS", pCS);
}



void qAssetMgr::CreateEngineMaterial()
{
	Ptr<qMaterial> pMtrl = nullptr;

	// Std2DMtrl
	pMtrl = new qMaterial(true);
	pMtrl->SetShader(FindAsset<qGraphicShader>(L"Std2DShader"));
	AddAsset(L"Std2DMtrl", pMtrl);

	// Std2DAlphaBlendMtrl
	pMtrl = new qMaterial(true);
	pMtrl->SetShader(FindAsset<qGraphicShader>(L"Std2DAlphaBlendShader"));
	AddAsset(L"Std2DAlphaBlendMtrl", pMtrl);

	// EffectMtrl
	pMtrl = new qMaterial(true);
	pMtrl->SetShader(FindAsset<qGraphicShader>(L"EffectShader"));
	AddAsset(L"EffectMtrl", pMtrl);

	// Std2D UI Mtrl
	pMtrl = new qMaterial(true);
	pMtrl->SetShader(FindAsset<qGraphicShader>(L"Std2DUIShader"));
	AddAsset(L"Std2DUIMtrl", pMtrl);

	// Std2D BOSS UI Mtrl
	pMtrl = new qMaterial(true);
	pMtrl->SetShader(FindAsset<qGraphicShader>(L"Std2DBOSSUIShader"));
	AddAsset(L"Std2DBOSSUIMtrl", pMtrl);

	// Std2D HUD Mtrl
	pMtrl = new qMaterial(true);
	pMtrl->SetShader(FindAsset<qGraphicShader>(L"Std2DHUDShader"));
	AddAsset(L"Std2DHUDMtrl", pMtrl);

	// Std2D BOSS HUD Mtrl
	pMtrl = new qMaterial(true);
	pMtrl->SetShader(FindAsset<qGraphicShader>(L"Std2DBOSSHUDShader"));
	AddAsset(L"Std2DBOSSHUDMtrl", pMtrl);

	// BlurMtrl
	pMtrl = new qMaterial(true);
	pMtrl->SetShader(FindAsset<qGraphicShader>(L"BlurShader"));
	AddAsset(L"BlurMtrl", pMtrl);

	// EffectMergeMtrl
	pMtrl = new qMaterial(true);
	pMtrl->SetShader(FindAsset<qGraphicShader>(L"EffectMergeShader"));
	AddAsset(L"EffectMergeMtrl", pMtrl);


	// DebugShapeMtrl
	pMtrl = new qMaterial(true);
	pMtrl->SetShader(FindAsset<qGraphicShader>(L"DebugShapeShader"));
	AddAsset(L"DebugShapeMtrl", pMtrl);

	// TileMapMtrl
	pMtrl = new qMaterial(true);
	pMtrl->SetShader(FindAsset<qGraphicShader>(L"TileMapShader"));
	AddAsset(L"TileMapMtrl", pMtrl);

	// ParticleRenderMtrl
	pMtrl = new qMaterial(true);
	pMtrl->SetShader(FindAsset<qGraphicShader>(L"ParticleRenderShader"));
	AddAsset(L"ParticleRenderMtrl", pMtrl);


	// GrayFilterMtrl
	pMtrl = new qMaterial(true);
	pMtrl->SetShader(FindAsset<qGraphicShader>(L"GrayFilterShader"));
	pMtrl->SetTexParam(TEX_0, FindAsset<qTexture>(L"PostProcessTex"));
	pMtrl->SetTexParam(TEX_1, FindAsset<qTexture>(L"texture\\noise\\noise_01.png"));
	pMtrl->SetTexParam(TEX_2, FindAsset<qTexture>(L"texture\\noise\\noise_02.png"));
	pMtrl->SetTexParam(TEX_3, FindAsset<qTexture>(L"texture\\noise\\noise_03.jpg"));
	pMtrl->SetTexParam(TEX_4, FindAsset<qTexture>(L"texture\\noise\\noise_04.jpg"));
	pMtrl->SetTexParam(TEX_5, FindAsset<qTexture>(L"texture\\noise\\noise_05.jpg"));
	AddAsset(L"GrayFilterMtrl", pMtrl);

	// DistortionMtrl
	pMtrl = new qMaterial(true);
	pMtrl->SetShader(FindAsset<qGraphicShader>(L"DistortionShader"));
	pMtrl->SetTexParam(TEX_0, FindAsset<qTexture>(L"PostProcessTex"));
	pMtrl->SetTexParam(TEX_1, FindAsset<qTexture>(L"texture\\noise\\noise_01.png"));
	pMtrl->SetTexParam(TEX_2, FindAsset<qTexture>(L"texture\\noise\\noise_02.png"));
	pMtrl->SetTexParam(TEX_3, FindAsset<qTexture>(L"texture\\noise\\noise_03.jpg"));
	pMtrl->SetTexParam(TEX_4, FindAsset<qTexture>(L"texture\\noise\\noise_04.jpg"));
	pMtrl->SetTexParam(TEX_5, FindAsset<qTexture>(L"texture\\noise\\noise_05.jpg"));
	AddAsset(L"DistortionMtrl", pMtrl);

	// Std3DMtrl
	pMtrl = new qMaterial(true);
	pMtrl->SetShader(FindAsset<qGraphicShader>(L"Std3DShader"));
	AddAsset(L"Std3DMtrl", pMtrl);

	// Std3D_DeferredMtrl
	pMtrl = new qMaterial(true);
	pMtrl->SetShader(FindAsset<qGraphicShader>(L"Std3D_DeferredShader"));
	AddAsset(L"Std3D_DeferredMtrl", pMtrl);

	// SkyBoxMtrl
	pMtrl = new qMaterial(true);
	pMtrl->SetShader(FindAsset<qGraphicShader>(L"SkyBoxShader"));
	AddAsset(L"SkyBoxMtrl", pMtrl);

	// DecalMtrl
	pMtrl = new qMaterial(true);
	pMtrl->SetShader(FindAsset<qGraphicShader>(L"DecalShader"));
	AddAsset(L"DecalMtrl", pMtrl);

	// DirLightShadowMapMtrl
	pMtrl = new qMaterial(true);
	pMtrl->SetShader(FindAsset<qGraphicShader>(L"DirLightShadowMap"));
	AddAsset(L"DirLightShadowMapMtrl", pMtrl);
}

