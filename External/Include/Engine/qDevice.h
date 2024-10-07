#pragma once

#include "qTexture.h"

// DirectX 관련 기능을 담당
// GPU 제어
class qConstBuffer;

class qDevice : public qSingleton<qDevice>
{
	SINGLE(qDevice);
	

public:
	int Init(HWND _hWnd, UINT _Width, UINT _Height);
	void Present() { m_SwapChain->Present(0, 0); }

public:
	ID3D11Device* GetDevice() { return m_Device.Get(); }
	ID3D11DeviceContext* GetContext() { return m_Context.Get(); }

	qConstBuffer* GetConstBuffer(CB_TYPE _Type) { return m_arrCB[(UINT)_Type]; }
	ID3D11RasterizerState* GetRSState(RS_TYPE _Type) { return m_RSState[(UINT)_Type].Get(); }

	ID3D11DepthStencilState* GetDSState(DS_TYPE _Type) { return m_DSState[(UINT)_Type].Get(); }
	ID3D11BlendState* GetBSState(BS_TYPE _Type) { return m_BSState[(UINT)_Type].Get(); }


	void ClearRenderTarget();

public:
	Vec2 GetResolution() { return m_vResolution; }

private:
	int CreateSwapChain();
	int CreateView();
	int CreateConstBuffer();
	int CreateRasterizeState();

	int CreateDepthStencilState();
	int CreateBlendState();

	int CreateSamplerState();


private:
	HWND								m_hWnd;
	Vec2								m_vResolution;


	ComPtr<ID3D11Device>				m_Device;		// Dx 11 객체 생성, GPU 메모리 할당
	ComPtr<ID3D11DeviceContext>			m_Context;		// Rendering

	ComPtr<IDXGISwapChain>				m_SwapChain;	// 렌더링된 이미지를 사용자에게 표시

	Ptr<qTexture>						m_RTTex;		// 랜더타겟 텍스처 텍스처 리소스의 속성을 가져옴
														// 리소스 데이터에 액세스하기 위한 렌더링 대상 뷰를 만듬

	Ptr<qTexture>						m_DSTex;		// 텍스처 리소스의 속성을 가져옴

	ComPtr<ID3D11RasterizerState>		m_RSState[(UINT)RS_TYPE::END];	// 레스터라이져 타입을 정하기(컬링 정하기)
	ComPtr<ID3D11SamplerState>			m_Sampler[3];	// 샘플러 상태 인터페이스에는 텍스처 샘플 작업에서 참조하기 위해 파이프라인 의 셰이더 단계에 바인딩할 수 있는 샘플러 상태에 대한 설명

	ComPtr<ID3D11DepthStencilState>		m_DSState[(UINT)DS_TYPE::END];		// 깊이 스텐실 테스트 중에 텍스처 리소스에 액세스함
	ComPtr<ID3D11BlendState>			m_BSState[(UINT)BS_TYPE::END];		// 혼합 상태 인터페이스는 출력 병합기에 바인딩할 수 있는 혼합 상태에 대한 설명을 포함



	qConstBuffer*						m_arrCB[(UINT)CB_TYPE::END];
};

