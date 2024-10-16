#include "pch.h"
#include "qRenderMgr.h"

#include "qAssetMgr.h"
#include "qGameObject.h"
#include "components.h"
#include "assets.h"

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
}


void qRenderMgr::CreateMRT()
{
	qMRT* pMRT = nullptr;

	// =============
	// SwapChain MRT
	// =============
	{
		Ptr<qTexture> arrRT[8] = { qAssetMgr::GetInst()->FindAsset<qTexture>(L"RenderTargetTex"), };
		Ptr<qTexture> pDSTex = qAssetMgr::GetInst()->FindAsset<qTexture>(L"DepthStencilTex");
		Vec4		  arrClearColor[8] = { Vec4(0.f, 0.f, 0.f, 0.f), };

		pMRT = new qMRT;
		pMRT->SetName(L"SwapChain");
		pMRT->Create(1, arrRT, pDSTex);
		pMRT->SetClearColor(arrClearColor, false);

		m_arrMRT[(UINT)MRT_TYPE::SWAPCHAIN] = pMRT;
	}

	// =============
	// Effect MRT
	// =============
	{
		Ptr<qTexture> arrRT[8] = { qAssetMgr::GetInst()->FindAsset<qTexture>(L"EffectTargetTex"), };
		Ptr<qTexture> pDSTex = qAssetMgr::GetInst()->FindAsset<qTexture>(L"EffectDepthStencilTex");
		Vec4		  arrClearColor[8] = { Vec4(0.f, 0.f, 0.f, 0.f), };

		pMRT = new qMRT;
		pMRT->SetName(L"Effect");
		pMRT->Create(1, arrRT, pDSTex);
		pMRT->SetClearColor(arrClearColor, false);

		m_arrMRT[(UINT)MRT_TYPE::EFFECT] = pMRT;
	}

	// ===============
	// EffectBlur MRT
	// ===============
	{
		Ptr<qTexture> arrRT[8] = { qAssetMgr::GetInst()->FindAsset<qTexture>(L"EffectBlurTargetTex"), };
		Ptr<qTexture> pDSTex = nullptr;
		Vec4		  arrClearColor[8] = { Vec4(0.f, 0.f, 0.f, 0.f), };

		pMRT = new qMRT;
		pMRT->SetName(L"EffectBlur");
		pMRT->Create(1, arrRT, nullptr);
		pMRT->SetClearColor(arrClearColor, false);

		m_arrMRT[(UINT)MRT_TYPE::EFFECT_BLUR] = pMRT;
	}
}