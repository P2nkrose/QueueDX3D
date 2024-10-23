#include "pch.h"
#include "qDevice.h"

#include "qConstBuffer.h"
#include "qAssetMgr.h"

qDevice::qDevice()
	: m_hWnd(nullptr)
	, m_arrCB{}
	, m_Sampler{}
{
}

qDevice::~qDevice()
{
	for (UINT i = 0; i < (UINT)CB_TYPE::END; ++i)
	{
		if (nullptr != m_arrCB[i])
			delete m_arrCB[i];
	}
}

int qDevice::Init(HWND _hWnd, UINT _Width, UINT _Height)
{
	// 윈도우 핸들 및 해상도 값 저장
	m_hWnd = _hWnd;

	m_vResolution.x = (float)_Width;
	m_vResolution.y = (float)_Height;


	// Device, Context 생성
	UINT Flag = 0;

#ifdef _DEBUG
	Flag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE
		, nullptr, Flag
		, nullptr, 0
		, D3D11_SDK_VERSION
		, m_Device.GetAddressOf(), nullptr, m_Context.GetAddressOf())))
	{
		MessageBox(nullptr, L"Device, Context 생성 실패", L"장치초기화 실패", MB_OK);
		return E_FAIL;
	}


	// Swap Chain
	if (FAILED(CreateSwapChain()))
	{
		MessageBox(nullptr, L"SwapChain 생성 실패", L"장치 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// RenderTargetView, DepthStencilView
	if (FAILED(CreateView()))
	{
		MessageBox(nullptr, L"View 생성 실패", L"장치 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// ViewPort 설정
	// 출력시킬 화면 윈도우 영역을 설정
	D3D11_VIEWPORT viewport = {};

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = m_vResolution.x;
	viewport.Height = m_vResolution.y;

	viewport.MinDepth = 0;
	viewport.MaxDepth = 1.f;

	CONTEXT->RSSetViewports(1, &viewport);

	if (FAILED(CreateConstBuffer()))
	{
		MessageBox(nullptr, L"상수버퍼 생성 실패", L"장치 초기화 실패", MB_OK);
		return E_FAIL;
	}

	if (FAILED(CreateRasterizeState()))
	{
		MessageBox(nullptr, L"레스터라이저 스테이트 생성 실패", L"장치 초기화 실패", MB_OK);
		return E_FAIL;
	}

	if (FAILED(CreateSamplerState()))
	{
		MessageBox(nullptr, L"샘플러 스테이트 생성 실패", L"장치 초기화 실패", MB_OK);
		return E_FAIL;
	}

	if (FAILED(CreateDepthStencilState()))
	{
		MessageBox(nullptr, L"DepthStencil 스테이트 생성 실패", L"장치 초기화 실패", MB_OK);
		return E_FAIL;
	}

	if (FAILED(CreateBlendState()))
	{
		MessageBox(nullptr, L"Blend 스테이트 생성 실패", L"장치 초기화 실패", MB_OK);
		return E_FAIL;
	}


	return S_OK;
}


void qDevice::ClearRenderTarget()
{
	CONTEXT->OMSetRenderTargets(0, nullptr, nullptr);
}

int qDevice::CreateSwapChain()
{
	// Swap Chain : 화면에 그림을 그리기 위한 버퍼를 관리하고,
	//				버퍼에 그려진 이미지를 화면 출력을 담당하는 객체
	DXGI_SWAP_CHAIN_DESC Desc = {};

	Desc.BufferCount						= 1;				// 백버퍼 갯수
	Desc.BufferDesc.Width					= m_vResolution.x;	// 백버퍼 해상도
	Desc.BufferDesc.Height					= m_vResolution.y;	// 백버퍼 해상도
	Desc.BufferDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;	// 픽셀 포맷
	Desc.BufferDesc.RefreshRate.Denominator = 60;	// 화면 갱신률
	Desc.BufferDesc.RefreshRate.Numerator	= 1;
	Desc.BufferDesc.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;
	Desc.BufferDesc.ScanlineOrdering		= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	Desc.BufferUsage						= DXGI_USAGE_RENDER_TARGET_OUTPUT;		// 버퍼의 사용 용도 (Render Target)
	Desc.Windowed							= true;	// 창모드 설정
	Desc.OutputWindow						= m_hWnd;		// SwapChain 버퍼의 이미지를 출력시킬 윈도우 핸들
	Desc.Flags								= 0;
	Desc.SampleDesc.Count					= 1;
	Desc.SampleDesc.Quality					= 0;
	Desc.SwapEffect							= DXGI_SWAP_EFFECT_DISCARD;


	ComPtr<IDXGIDevice>		Device = nullptr;
	ComPtr<IDXGIAdapter>	Adapter = nullptr;
	ComPtr<IDXGIFactory>	Factory = nullptr;

	if (FAILED(m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)Device.GetAddressOf())))
		return E_FAIL;

	if (FAILED(Device->GetParent(__uuidof(IDXGIAdapter), (void**)Adapter.GetAddressOf())))
		return E_FAIL;

	if (FAILED(Adapter->GetParent(_uuidof(IDXGIFactory), (void**)Factory.GetAddressOf())))
		return E_FAIL;

	if (FAILED(Factory->CreateSwapChain(m_Device.Get(), &Desc, m_SwapChain.GetAddressOf())))
		return E_FAIL;


	return S_OK;
}

int qDevice::CreateView()
{
	// ===========================================================
	//   RenderTarget Texture, DepthStencil Texture 를 생성시킨다.
	// ===========================================================

	// 스왚체인의 백버퍼의 주소를 받아온다.
	ComPtr<ID3D11Texture2D> RenderTargetTex;
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)RenderTargetTex.GetAddressOf());
	m_RTTex = qAssetMgr::GetInst()->CreateTexture(L"RenderTargetTex", RenderTargetTex);

	// DepthStencil 텍스쳐 생성
	m_DSTex = qAssetMgr::GetInst()->CreateTexture(L"DepthStencilTex"
											, (UINT)m_vResolution.x, (UINT)m_vResolution.y
											, DXGI_FORMAT_D24_UNORM_S8_UINT, D3D11_BIND_DEPTH_STENCIL);


	// 렌더타겟 및 DepthStencilTex 타겟 지정
	CONTEXT->OMSetRenderTargets(1, m_RTTex->GetRTV().GetAddressOf(), m_DSTex->GetDSV().Get());


	// View에는 여러가지 종류가 있음
	// RenderTargetView
	// DepthStencilView
	// ShaderResourceView
	// UnorderedAccessView

	return S_OK;
}

int qDevice::CreateConstBuffer()
{
	qConstBuffer* pCB = nullptr;

	// 월드, 뷰, 투영 행렬 전달
	pCB = new qConstBuffer;
	
	if(FAILED(pCB->Create(CB_TYPE::TRANSFORM, sizeof(tTransform))))
	{
		MessageBox(nullptr, L"상수버퍼 생성 실패", L"View 생성 실패", MB_OK);
		return E_FAIL;
	}

	m_arrCB[(UINT)CB_TYPE::TRANSFORM] = pCB;

	pCB = new qConstBuffer;
	if (FAILED(pCB->Create(CB_TYPE::MATERIAL, sizeof(tMtrlConst))))
	{
		MessageBox(nullptr, L"상수버퍼 생성 실패", L"초기화 실패", MB_OK);
		return E_FAIL;
	}

	m_arrCB[(UINT)CB_TYPE::MATERIAL] = pCB;


	pCB = new qConstBuffer;
	if (FAILED(pCB->Create(CB_TYPE::SPRITE, sizeof(tSpriteInfo))))
	{
		MessageBox(nullptr, L"상수버퍼 생성 실패", L"초기화 실패", MB_OK);
		return E_FAIL;
	}
	m_arrCB[(UINT)CB_TYPE::SPRITE] = pCB;


	pCB = new qConstBuffer;
	if (FAILED(pCB->Create(CB_TYPE::HUD, sizeof(tHUD))))
	{
		MessageBox(nullptr, L"상수버퍼 생성 실패", L"초기화 실패", MB_OK);
		return E_FAIL;
	}
	m_arrCB[(UINT)CB_TYPE::HUD] = pCB;


	pCB = new qConstBuffer;
	if (FAILED(pCB->Create(CB_TYPE::BOSSHUD, sizeof(tBOSSHUD))))
	{
		MessageBox(nullptr, L"상수버퍼 생성 실패", L"초기화 실패", MB_OK);
		return E_FAIL;
	}
	m_arrCB[(UINT)CB_TYPE::BOSSHUD] = pCB;


	pCB = new qConstBuffer;
	if (FAILED(pCB->Create(CB_TYPE::GLOBAL, sizeof(tGlobalData))))
	{
		MessageBox(nullptr, L"상수버퍼 생성 실패", L"초기화 실패", MB_OK);
		return E_FAIL;
	}
	m_arrCB[(UINT)CB_TYPE::GLOBAL] = pCB;



	return S_OK;
}

int qDevice::CreateRasterizeState()
{
	D3D11_RASTERIZER_DESC Desc = {};

	// Cull Back
	m_RSState[(UINT)RS_TYPE::CULL_BACK] = nullptr;

	// Cull Front
	Desc.CullMode = D3D11_CULL_FRONT;
	Desc.FillMode = D3D11_FILL_SOLID;
	DEVICE->CreateRasterizerState(&Desc, m_RSState[(UINT)RS_TYPE::CULL_FRONT].GetAddressOf());

	// Cull None
	Desc.CullMode = D3D11_CULL_NONE;
	Desc.FillMode = D3D11_FILL_SOLID;
	DEVICE->CreateRasterizerState(&Desc, m_RSState[(UINT)RS_TYPE::CULL_NONE].GetAddressOf());

	// Wire Frame
	Desc.CullMode = D3D11_CULL_NONE;
	Desc.FillMode = D3D11_FILL_WIREFRAME;
	DEVICE->CreateRasterizerState(&Desc, m_RSState[(UINT)RS_TYPE::WIRE_FRAME].GetAddressOf());

	return S_OK;
}

int qDevice::CreateDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC Desc = {};

	// Less : 더 작은 깊이가 통과
	m_DSState[(UINT)DS_TYPE::LESS] = nullptr;


	// Less Equal : 깊이가 작거나 같으면 통과
	Desc.DepthEnable = true;								// 깊이 판정을 진행
	Desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;			// 깊이 판정 방식
	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;		// 깊이 판정을 성공시 깊이 기록여부
	Desc.StencilEnable = false;

	if (FAILED(DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::LESS_EQUAL].GetAddressOf())))
	{
		return E_FAIL;
	}


	// Greater : 더 큰 깊이가 통과
	Desc.DepthEnable = true;
	Desc.DepthFunc = D3D11_COMPARISON_GREATER;
	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	Desc.StencilEnable = false;

	if (FAILED(DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::GREATER].GetAddressOf())))
	{
		return E_FAIL;
	}


	// NO_TEST
	Desc.DepthEnable = true;						// 깊이 판정은 하지만
	Desc.DepthFunc = D3D11_COMPARISON_ALWAYS;		// 깊이에 상관없이 모두 투영을 통과시킨다
	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	Desc.StencilEnable = false;

	if (FAILED(DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::NO_TEST].GetAddressOf())))
	{
		return E_FAIL;
	}


	// NO_WRITE
	Desc.DepthEnable = true;							// 깊이 판정을 진행
	Desc.DepthFunc = D3D11_COMPARISON_LESS;				// 깊이 판정 방식
	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;	// 깊이 판정을 성공 시 깊이 기록 여부 (깊이 기록을 하지 않는다)
	Desc.StencilEnable = false;

	if (FAILED(DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::NO_WRITE].GetAddressOf())))
	{
		return E_FAIL;
	}


	// NO_TEST_NO_WRITE
	Desc.DepthEnable = true;
	Desc.DepthFunc = D3D11_COMPARISON_ALWAYS;				// 모두 통과시키지만
	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;		// 자신의 깊이 기록을 하지 않는다
	Desc.StencilEnable = false;

	if (FAILED(DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::NO_TEST_NO_WRITE].GetAddressOf())))
	{
		return E_FAIL;
	}


	//// INNER - VolumeMesh 뒷변보다 앞쪽에 있는 부분 체크
	//Desc.DepthEnable = true;    // 깊이판정을 진행
	//Desc.DepthFunc = D3D11_COMPARISON_GREATER;           // 깊이 판정 방식
	//Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;   // 깊이판정을 성공시 깊이 기록여부
	//Desc.StencilEnable = true;
	//
	//Desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;  // 항상 통과    
	//Desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;    // 깊이가 실패(뒷면보다 더 멀다)
	//Desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;    // 스텐실 테스트는 항상 통과기 때문에 발생할 일이 없다.
	//Desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_INCR;    // 스텐실 값을 증가시킨다.
	//
	//
	//Desc.FrontFace.StencilFunc;
	//Desc.FrontFace.StencilPassOp;
	//Desc.FrontFace.StencilDepthFailOp;
	//Desc.FrontFace.StencilDepthFailOp;
	//
	//if (FAILED(DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::NO_TEST_NO_WRITE].GetAddressOf())))
	//{
	//	return E_FAIL;
	//}
	//
	//
	//// OUTER - VolumeMesh 앞면보다 뒤에 있는 부분 체크
	//Desc.DepthEnable = true;    // 깊이판정을 진행
	//Desc.DepthFunc = D3D11_COMPARISON_LESS;          // 깊이 판정 방식
	//Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;   // 깊이판정을 성공시 깊이 기록여부
	//Desc.StencilEnable = true;
	//
	//Desc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL; // 특정값(1) 이랑 동일할 경우 Stencil 통과
	//Desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;  // 스텐실 실패 == Inner 체크 성공을 못한 부분들, 아무것도 할 필요가 없다.
	//Desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;  // 스텐실 성공, 깊이 실패, 뒷면보다는 안쪽에 있었지만 앞면보다도 더 앞쪽에 있었다    
	//Desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;  // 스텐실 성공, 깊이 성공, 뒷면보다 안쪽에, 앞면보다 뒷쪽에, 볼륨메쉬 내부영역
	//
	//Desc.BackFace.StencilFunc;
	//Desc.BackFace.StencilPassOp;
	//Desc.BackFace.StencilDepthFailOp;
	//Desc.BackFace.StencilDepthFailOp;
	//
	//if (FAILED(DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::NO_TEST_NO_WRITE].GetAddressOf())))
	//{
	//	return E_FAIL;
	//}







	return S_OK;

}

int qDevice::CreateBlendState()
{
	D3D11_BLEND_DESC Desc = {};

	// Default
	m_BSState[(UINT)BS_TYPE::DEFAULT] = nullptr;


	// AlphaBlend - Coverage
	Desc.AlphaToCoverageEnable = true;		// true로 하게되면 discard 처럼 알파값이 자동으로 깊이판정안함
	Desc.IndependentBlendEnable = false;

	Desc.RenderTarget[0].BlendEnable = true;
	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;


	// Src(Pixel RGB) * Alpha  +   Dest(RenderTarget RGB) * (1 - Alpha)
	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;			// 계수
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;		// 계수 (인버스)

	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;


	if (FAILED(DEVICE->CreateBlendState(&Desc, m_BSState[(UINT)BS_TYPE::ALPHABLEND_COVERAGE].GetAddressOf())))
	{
		return E_FAIL;
	}


	// AlphaBlend
	Desc.AlphaToCoverageEnable = false;
	Desc.IndependentBlendEnable = false;

	Desc.RenderTarget[0].BlendEnable = true;
	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	// Src(Pixel RGB) * A     +      Dest(RenderTarget RGB) * (1 - A)
	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // 계수
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; // 계수

	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;


	if (FAILED(DEVICE->CreateBlendState(&Desc, m_BSState[(UINT)BS_TYPE::ALPHABLEND].GetAddressOf())))
	{
		return E_FAIL;
	}

	// ONE - ONE Blend
	Desc.AlphaToCoverageEnable = false;
	Desc.IndependentBlendEnable = false;

	Desc.RenderTarget[0].BlendEnable = true;
	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	// Src(Pixel RGB) * 1  +  Dest(RenderTarget RGB) * 1
	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE; // 계수
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE; // 계수

	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

	if (FAILED(DEVICE->CreateBlendState(&Desc, m_BSState[(UINT)BS_TYPE::ONE_ONE].GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;

}

int qDevice::CreateSamplerState()
{
	D3D11_SAMPLER_DESC Desc = {};

	Desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.Filter = D3D11_FILTER_ANISOTROPIC; // 이방성 필터링

	if (FAILED(DEVICE->CreateSamplerState(&Desc, m_Sampler[0].GetAddressOf())))
	{
		return E_FAIL;
	}

	Desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT; // 포인트 필터링

	if (FAILED(DEVICE->CreateSamplerState(&Desc, m_Sampler[1].GetAddressOf())))
	{
		return E_FAIL;
	}

	Desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; // 포인트 필터링

	if (FAILED(DEVICE->CreateSamplerState(&Desc, m_Sampler[2].GetAddressOf())))
	{
		return E_FAIL;
	}


	CONTEXT->VSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());
	CONTEXT->HSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());
	CONTEXT->DSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());
	CONTEXT->GSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());
	CONTEXT->PSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());
	CONTEXT->CSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());

	CONTEXT->VSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());
	CONTEXT->HSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());
	CONTEXT->DSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());
	CONTEXT->GSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());
	CONTEXT->PSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());
	CONTEXT->CSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());

	CONTEXT->VSSetSamplers(2, 1, m_Sampler[2].GetAddressOf());
	CONTEXT->HSSetSamplers(2, 1, m_Sampler[2].GetAddressOf());
	CONTEXT->DSSetSamplers(2, 1, m_Sampler[2].GetAddressOf());
	CONTEXT->GSSetSamplers(2, 1, m_Sampler[2].GetAddressOf());
	CONTEXT->PSSetSamplers(2, 1, m_Sampler[2].GetAddressOf());
	CONTEXT->CSSetSamplers(2, 1, m_Sampler[2].GetAddressOf());

	return S_OK;
}
