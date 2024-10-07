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
	pMesh = new qMesh;
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
	
	arrVtx[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVtx[0].vUV = Vec2(0.f, 0.f);
	
	arrVtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrVtx[1].vUV = Vec2(1.f, 0.f);
	
	arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrVtx[2].vUV = Vec2(1.f, 1.f);
	
	arrVtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[3].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVtx[3].vUV = Vec2(0.f, 1.f);
	
	// Index 버퍼 생성
	UINT arrIdx[6] = {};
	arrIdx[0] = 0;		arrIdx[1] = 1;		arrIdx[2] = 2;
	arrIdx[3] = 0;		arrIdx[4] = 2;		arrIdx[5] = 3;
	
	pMesh = new qMesh;
	pMesh->Create(arrVtx, 4, arrIdx, 6);
	pMesh->SetEngineAsset();
	AddAsset(L"RectMesh", pMesh);
	
	// RectMesh_Debug
	arrIdx[0] = 0;	arrIdx[1] = 1;	arrIdx[2] = 2;	arrIdx[3] = 3;	arrIdx[4] = 0;
	
	pMesh = new qMesh;
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
	
	pMesh = new qMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	pMesh->SetEngineAsset();
	AddAsset(L"CircleMesh", pMesh);
	
	
	// CircleMesh_Debug
	vecIdx.clear();
	
	for (size_t i = 0; i < vecVtx.size(); ++i)
	{
		vecIdx.push_back((UINT)i);
	}
	
	pMesh = new qMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	pMesh->SetEngineAsset();
	AddAsset(L"CircleMesh_Debug", pMesh);
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
	//pShader->SetRSType(RS_TYPE::WIRE_FRAME);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::DEFAULT);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_DEBUG);

	AddAsset(L"DebugShapeShader", pShader);

	
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


}

