#include "pch.h"
#include "qRenderMgr.h"

#include "qAssetMgr.h"
#include "qGameObject.h"
#include "components.h"
#include "assets.h"

#include "qDevice.h"
#include "qMRT.h"

void qRenderMgr::Init()
{
	// Asset Manager가 초기화뙬때 만들어둔 후처리용 텍스처를 참조한다.
	m_PostProcessTex = qAssetMgr::GetInst()->FindAsset<qTexture>(L"PostProcessTex");


	// 디버그 렌더링용 게임 오브젝트
	m_DebugObject = new qGameObject;
	m_DebugObject->AddComponent(new qTransform);
	m_DebugObject->AddComponent(new qMeshRender);
	m_DebugObject->MeshRender()->SetMaterial(qAssetMgr::GetInst()->FindAsset<qMaterial>(L"DebugShapeMtrl"));

	// MRT 생성
	CreateMRT();

	// RenderMgr 전용 재질 생성
	CreateMaterial();
}


void qRenderMgr::CreateMRT()
{

	// =============
	// SwapChain MRT
	// =============
	{
		Ptr<qTexture> arrRT[8] = { qAssetMgr::GetInst()->FindAsset<qTexture>(L"RenderTargetTex"), };
		Ptr<qTexture> pDSTex = qAssetMgr::GetInst()->FindAsset<qTexture>(L"DepthStencilTex");
		Vec4		  arrClearColor[8] = { Vec4(0.f, 0.f, 0.f, 0.f), };

		
		m_arrMRT[(UINT)MRT_TYPE::SWAPCHAIN] = new qMRT;
		m_arrMRT[(UINT)MRT_TYPE::SWAPCHAIN]->SetName(L"SwapChain");
		m_arrMRT[(UINT)MRT_TYPE::SWAPCHAIN]->Create(1, arrRT, pDSTex);
		m_arrMRT[(UINT)MRT_TYPE::SWAPCHAIN]->SetClearColor(arrClearColor, false);
	}

	// =============
	// Effect MRT
	// =============
	{
		Ptr<qTexture> arrRT[8] = { qAssetMgr::GetInst()->FindAsset<qTexture>(L"EffectTargetTex"), };
		Ptr<qTexture> pDSTex = qAssetMgr::GetInst()->FindAsset<qTexture>(L"EffectDepthStencilTex");
		Vec4		  arrClearColor[8] = { Vec4(0.f, 0.f, 0.f, 0.f), };

		m_arrMRT[(UINT)MRT_TYPE::EFFECT] = new qMRT;
		m_arrMRT[(UINT)MRT_TYPE::EFFECT]->SetName(L"Effect");
		m_arrMRT[(UINT)MRT_TYPE::EFFECT]->Create(1, arrRT, pDSTex);
		m_arrMRT[(UINT)MRT_TYPE::EFFECT]->SetClearColor(arrClearColor, false);
	}

	// ===============
	// EffectBlur MRT
	// ===============
	{
		Ptr<qTexture> arrRT[8] = { qAssetMgr::GetInst()->FindAsset<qTexture>(L"EffectBlurTargetTex"), };
		Ptr<qTexture> pDSTex = nullptr;
		Vec4		  arrClearColor[8] = { Vec4(0.f, 0.f, 0.f, 0.f), };

		m_arrMRT[(UINT)MRT_TYPE::EFFECT_BLUR] = new qMRT;
		m_arrMRT[(UINT)MRT_TYPE::EFFECT_BLUR]->SetName(L"EffectBlur");
		m_arrMRT[(UINT)MRT_TYPE::EFFECT_BLUR]->Create(1, arrRT, nullptr);
		m_arrMRT[(UINT)MRT_TYPE::EFFECT_BLUR]->SetClearColor(arrClearColor, false);
	}

	// ============
	//   Deferred
	// ============

	{
		Vec2 vResolution = qDevice::GetInst()->GetResolution();

		Ptr<qTexture> arrRT[8] =
		{
			qAssetMgr::GetInst()->CreateTexture(L"AlbedoTargetTex"
											, (UINT)vResolution.x, (UINT)vResolution.y
											, DXGI_FORMAT_R8G8B8A8_UNORM
											, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE),
			qAssetMgr::GetInst()->CreateTexture(L"NormalTargetTex"
											, (UINT)vResolution.x, (UINT)vResolution.y
											, DXGI_FORMAT_R32G32B32A32_FLOAT
											, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE),
			qAssetMgr::GetInst()->CreateTexture(L"PositionTargetTex"
											, (UINT)vResolution.x, (UINT)vResolution.y
											, DXGI_FORMAT_R32G32B32A32_FLOAT
											, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE),
			qAssetMgr::GetInst()->CreateTexture(L"EmissiveTargetTex"
											, (UINT)vResolution.x, (UINT)vResolution.y
											, DXGI_FORMAT_R32G32B32A32_FLOAT
											, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE),
			qAssetMgr::GetInst()->CreateTexture(L"DataTargetTex"
											, (UINT)vResolution.x, (UINT)vResolution.y
											, DXGI_FORMAT_R32G32B32A32_FLOAT
											, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE),
		};

		Ptr<qTexture> pDSTex = qAssetMgr::GetInst()->FindAsset<qTexture>(L"DepthStencilTex");
		Vec4		  arrClearColor[8] = { Vec4(0.f, 0.f, 0.f, 0.f), };

		m_arrMRT[(UINT)MRT_TYPE::DEFERRED] = new qMRT;
		m_arrMRT[(UINT)MRT_TYPE::DEFERRED]->SetName(L"Deferred");
		m_arrMRT[(UINT)MRT_TYPE::DEFERRED]->Create(5, arrRT, pDSTex);
		m_arrMRT[(UINT)MRT_TYPE::DEFERRED]->SetClearColor(arrClearColor, false);

	}

	// ==============
	//     LIGHT
	// ==============

	{
		Vec2 vResolution = qDevice::GetInst()->GetResolution();

		Ptr<qTexture> arrRT[8] =
		{
			qAssetMgr::GetInst()->CreateTexture(L"DiffuseTargetTex"
											, (UINT)vResolution.x, (UINT)vResolution.y
											, DXGI_FORMAT_R32G32B32A32_FLOAT
											, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE),
			qAssetMgr::GetInst()->CreateTexture(L"SpecularTargetTex"
											, (UINT)vResolution.x, (UINT)vResolution.y
											, DXGI_FORMAT_R32G32B32A32_FLOAT
											, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE),
		};
		Ptr<qTexture> pDSTex = nullptr;
		Vec4		  arrClearColor[8] = { Vec4(0.f, 0.f, 0.f, 0.f), };

		m_arrMRT[(UINT)MRT_TYPE::LIGHT] = new qMRT;
		m_arrMRT[(UINT)MRT_TYPE::LIGHT]->SetName(L"Light");
		m_arrMRT[(UINT)MRT_TYPE::LIGHT]->Create(2, arrRT, pDSTex);
		m_arrMRT[(UINT)MRT_TYPE::LIGHT]->SetClearColor(arrClearColor, false);
	}


	// =====
	// DECAL
	// =====
	{
		Vec2 vResolution = qDevice::GetInst()->GetResolution();

		Ptr<qTexture> arrRT[8] =
		{
			qAssetMgr::GetInst()->FindAsset<qTexture>(L"AlbedoTargetTex"),
			qAssetMgr::GetInst()->FindAsset<qTexture>(L"EmissiveTargetTex"),
		};

		Ptr<qTexture> pDSTex = nullptr;
		Vec4		  arrClearColor[8] = { Vec4(0.f, 0.f, 0.f, 0.f), };

		m_arrMRT[(UINT)MRT_TYPE::DECAL] = new qMRT;
		m_arrMRT[(UINT)MRT_TYPE::DECAL]->SetName(L"Decal");
		m_arrMRT[(UINT)MRT_TYPE::DECAL]->Create(2, arrRT, pDSTex);
		m_arrMRT[(UINT)MRT_TYPE::DECAL]->SetClearColor(arrClearColor, false);
	}


}


void qRenderMgr::ClearMRT()
{
	m_arrMRT[(UINT)MRT_TYPE::SWAPCHAIN]->Clear();
	m_arrMRT[(UINT)MRT_TYPE::DEFERRED]->ClearRT();
	m_arrMRT[(UINT)MRT_TYPE::LIGHT]->ClearRT();
}

void qRenderMgr::CreateMaterial()
{
	// DirLightShader
	Ptr<qGraphicShader> pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\light.fx", "VS_DirLight");
	pShader->CreatePixelShader(L"shader\\light.fx", "PS_DirLight");
	pShader->SetRSType(RS_TYPE::CULL_BACK);
	pShader->SetBSType(BS_TYPE::ONE_ONE);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_LIGHT);
	qAssetMgr::GetInst()->AddAsset(L"DirLightShader", pShader);

	// DirLightMtrl
	Ptr<qMaterial> pMtrl = new qMaterial(true);
	pMtrl->SetShader(pShader);
	pMtrl->SetTexParam(TEX_0, qAssetMgr::GetInst()->FindAsset<qTexture>(L"PositionTargetTex"));
	pMtrl->SetTexParam(TEX_1, qAssetMgr::GetInst()->FindAsset<qTexture>(L"NormalTargetTex"));
	qAssetMgr::GetInst()->AddAsset(L"DirLightMtrl", pMtrl);


	// PointLightShader
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\light.fx", "VS_PointLight");
	pShader->CreatePixelShader(L"shader\\light.fx", "PS_PointLight");
	pShader->SetRSType(RS_TYPE::CULL_FRONT);
	pShader->SetBSType(BS_TYPE::ONE_ONE);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_LIGHT);
	qAssetMgr::GetInst()->AddAsset(L"PointLightShader", pShader);

	// PointLightMtrl
	pMtrl = new qMaterial(true);
	pMtrl->SetShader(pShader);
	pMtrl->SetTexParam(TEX_0, qAssetMgr::GetInst()->FindAsset<qTexture>(L"PositionTargetTex"));
	pMtrl->SetTexParam(TEX_1, qAssetMgr::GetInst()->FindAsset<qTexture>(L"NormalTargetTex"));
	qAssetMgr::GetInst()->AddAsset(L"PointLightMtrl", pMtrl);


	// MergeShader
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\merge.fx", "VS_Merge");
	pShader->CreatePixelShader(L"shader\\merge.fx", "PS_Merge");
	pShader->SetRSType(RS_TYPE::CULL_BACK);
	pShader->SetBSType(BS_TYPE::DEFAULT);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_NONE);

	// MergeMtrl
	m_MergeMtrl = new qMaterial(true);
	m_MergeMtrl->SetShader(pShader);
	m_MergeMtrl->SetTexParam(TEX_0, qAssetMgr::GetInst()->FindAsset<qTexture>(L"AlbedoTargetTex"));
	m_MergeMtrl->SetTexParam(TEX_1, qAssetMgr::GetInst()->FindAsset<qTexture>(L"DiffuseTargetTex"));
	m_MergeMtrl->SetTexParam(TEX_2, qAssetMgr::GetInst()->FindAsset<qTexture>(L"SpecularTargetTex"));
	m_MergeMtrl->SetTexParam(TEX_3, qAssetMgr::GetInst()->FindAsset<qTexture>(L"EmissiveTargetTex"));

	// RectMesh
	m_RectMesh = qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh");

	// DecalMtrl
	Ptr<qMaterial> pDecalMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"DecalMtrl");
	pDecalMtrl->SetTexParam(TEX_0, qAssetMgr::GetInst()->FindAsset<qTexture>(L"PositionTargetTex"));
}
