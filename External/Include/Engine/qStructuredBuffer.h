#pragma once
#include "qEntity.h"

enum SB_TYPE
{
	SRV_ONLY,
	SRV_UAV,
};

class qStructuredBuffer : public qEntity
{
public:
	CLONE_DISABLE(qStructuredBuffer);
	qStructuredBuffer();
	~qStructuredBuffer();

public:
	int Create(UINT _ElementSize, UINT _ElementCount, SB_TYPE _Type, bool _SysMemMove = false, void* _InitData = nullptr);

public:
	UINT GetElementCount() { return m_ElementCount; }
	UINT GetElementSize() { return m_ElementSize; }
	UINT GetBufferSize() { return m_ElementCount * m_ElementSize; }

	void SetData(void* _pData, UINT _DataSize = 0);
	void GetData(void* _pData, UINT _DataSize = 0);

	// Graphic Shader - t register
	void Binding(UINT _RegisterNum);
	void Clear(UINT _RegisterNum);

	// Compute Shader - t register
	void Binding_CS_SRV(UINT _RegisterNum);
	void Clear_CS_SRV();

	// Compute Shader - u register
	void Binding_CS_UAV(UINT _RegisterNum);
	void Clear_CS_UAV();


private:
	ComPtr<ID3D11Buffer>					m_SB;
	ComPtr<ID3D11Buffer>					m_SB_Write;
	ComPtr<ID3D11Buffer>					m_SB_Read;

	D3D11_BUFFER_DESC						m_Desc;
	ComPtr<ID3D11ShaderResourceView>		m_SRV;
	ComPtr<ID3D11UnorderedAccessView>		m_UAV;


	SB_TYPE									m_Type;
	bool									m_SysMemMove;

	UINT									m_ElementCount;
	UINT									m_ElementSize;

	UINT									m_RecentRegisterNum;
};

