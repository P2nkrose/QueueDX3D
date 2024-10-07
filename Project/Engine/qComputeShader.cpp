#include "pch.h"
#include "qComputeShader.h"

#include "qDevice.h"
#include "qConstBuffer.h"
#include "qPathMgr.h"


qComputeShader::qComputeShader(UINT _ThreadPerGroupX, UINT _ThreadPerGroupY, UINT _ThreadPerGroupZ, const wstring& _ShaderRelativePath, const string& _FuncName)
	: qShader(ASSET_TYPE::COMPUTE_SHADER)
	, m_ThreadPerGroupX(_ThreadPerGroupX)
	, m_ThreadPerGroupY(_ThreadPerGroupY)
	, m_ThreadPerGroupZ(_ThreadPerGroupZ)
	, m_GroupX(1)
	, m_GroupY(1)
	, m_GroupZ(1)
	, m_Const{}
{
	CreateComputeShader(_ShaderRelativePath, _FuncName);
}

qComputeShader::~qComputeShader()
{
}

int qComputeShader::Execute()
{
	if (FAILED(Binding()))
		return E_FAIL;

	// 상수데이터 전달
	qConstBuffer* pCB = qDevice::GetInst()->GetConstBuffer(CB_TYPE::MATERIAL);
	pCB->SetData(&m_Const);
	pCB->Binding_CS();

	// 필요한 그룹 수 계산
	CalcGroupNum();

	// 컴퓨트 쉐이더 실행
	CONTEXT->CSSetShader(m_CS.Get(), 0, 0);
	CONTEXT->Dispatch(m_GroupX, m_GroupY, m_GroupZ);

	// 리소스 해제
	Clear();
}

int qComputeShader::CreateComputeShader(const wstring& _RelativePath, const string& _FuncName)
{
	wstring strFilePath = qPathMgr::GetInst()->GetContentPath();
	strFilePath += _RelativePath;

	HRESULT hr = D3DCompileFromFile(strFilePath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _FuncName.c_str(), "cs_5_0", D3DCOMPILE_DEBUG, 0
		, m_CSBlob.GetAddressOf(), m_ErrBlob.GetAddressOf());

	if (FAILED(hr))
	{
		if (nullptr != m_ErrBlob)
		{
			MessageBoxA(nullptr, (char*)m_ErrBlob->GetBufferPointer(), "쉐이더 컴파일 실패", MB_OK);
		}
		else
		{
			errno_t err = GetLastError();
			wchar_t szErrMsg[255] = {};
			swprintf_s(szErrMsg, 255, L"Error Code : %d", err);
			MessageBox(nullptr, szErrMsg, L"쉐이더 컴파일 실패", MB_OK);
		}

		return E_FAIL;
	}

	DEVICE->CreateComputeShader(m_CSBlob->GetBufferPointer()
		, m_CSBlob->GetBufferSize(), nullptr, m_CS.GetAddressOf());

	return S_OK;
}
