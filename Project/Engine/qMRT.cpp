#include "pch.h"
#include "qMRT.h"

#include "qDevice.h"

qMRT::qMRT()
	: m_arrRT{}
	, m_ClearColor{}
	, m_RTCount(0)
	, m_ViewPort{}
{
}

qMRT::~qMRT()
{
}

void qMRT::Create(int _RTCount, Ptr<qTexture>* _arrRT, Ptr<qTexture> _DSTex)
{
	m_RTCount = _RTCount;

	for (int i = 0; i < 8; ++i)
	{
		if (i < _RTCount)
			m_arrRT[i] = _arrRT[i];
		else
			m_arrRT[i] = nullptr;
	}

	m_DSTex = _DSTex;

	Ptr<qTexture> pTarget = m_arrRT[0];
	if (nullptr == pTarget)
		pTarget = m_DSTex;
	assert(pTarget);

	// ViewPort ¼³Á¤
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_ViewPort.Width = pTarget->Width();
	m_ViewPort.Height = pTarget->Height();
	m_ViewPort.MinDepth = 0.f;
	m_ViewPort.MaxDepth = 1.f;
}

void qMRT::SetClearColor(Vec4* _Color, bool _Independent)
{
	if (_Independent)
	{
		for (int i = 0; i < m_RTCount; ++i)
		{
			m_ClearColor[i] = _Color[i];
		}
	}

	else
	{
		for (int i = 0; i < m_RTCount; ++i)
		{
			m_ClearColor[i] = _Color[0];
		}
	}
}

void qMRT::OMSet()
{
	ID3D11RenderTargetView* arrRTV[8] = {};
	for (int i = 0; i < m_RTCount; ++i)
	{
		arrRTV[i] = m_arrRT[i]->GetRTV().Get();
	}

	ComPtr<ID3D11DepthStencilView> pDSV = nullptr;
	if (nullptr != m_DSTex)
		pDSV = m_DSTex->GetDSV();

	CONTEXT->OMSetRenderTargets(m_RTCount, arrRTV, pDSV.Get());
	CONTEXT->RSSetViewports(1, &m_ViewPort);
}

void qMRT::ClearRT()
{
	for (int i = 0; i < m_RTCount; ++i)
	{
		CONTEXT->ClearRenderTargetView(m_arrRT[i]->GetRTV().Get(), m_ClearColor[i]);
	}
}

void qMRT::ClearDS()
{
	if (nullptr == m_DSTex)
		return;

	CONTEXT->ClearDepthStencilView(m_DSTex->GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}
