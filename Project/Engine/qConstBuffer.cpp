#include "pch.h"
#include "qConstBuffer.h"

#include "qDevice.h"

qConstBuffer::qConstBuffer()
	: m_Desc{}
{
}

qConstBuffer::~qConstBuffer()
{
}

int qConstBuffer::Create(CB_TYPE _type, UINT _BufferSize)
{
	assert(0 == (_BufferSize % 16));

	m_CBType = _type;

	m_Desc.ByteWidth = _BufferSize;
	m_Desc.Usage = D3D11_USAGE_DYNAMIC;
	m_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	if (FAILED(DEVICE->CreateBuffer(&m_Desc, nullptr, m_CB.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

void qConstBuffer::SetData(void* _pData)
{
	// 전역변수에 있는 정점 데이터를 상수버퍼로 쓰기
	D3D11_MAPPED_SUBRESOURCE tMapSub = {};
	CONTEXT->Map(m_CB.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &tMapSub);
	memcpy(tMapSub.pData, _pData, m_Desc.ByteWidth);
	CONTEXT->Unmap(m_CB.Get(), 0);
}


void qConstBuffer::Binding()
{
	// 상수버퍼 바인딩, b0 레지스터에, Vertex Shader 시점에, g_CB 에 있는 값이 0번 레지스터에 바인딩 될 예정
	CONTEXT->VSSetConstantBuffers((UINT)m_CBType, 1, m_CB.GetAddressOf());
	CONTEXT->HSSetConstantBuffers((UINT)m_CBType, 1, m_CB.GetAddressOf());
	CONTEXT->DSSetConstantBuffers((UINT)m_CBType, 1, m_CB.GetAddressOf());
	CONTEXT->GSSetConstantBuffers((UINT)m_CBType, 1, m_CB.GetAddressOf());
	CONTEXT->PSSetConstantBuffers((UINT)m_CBType, 1, m_CB.GetAddressOf());
	CONTEXT->CSSetConstantBuffers((UINT)m_CBType, 1, m_CB.GetAddressOf());
}

void qConstBuffer::Binding_CS()
{
	CONTEXT->CSSetConstantBuffers((UINT)m_CBType, 1, m_CB.GetAddressOf());
}
