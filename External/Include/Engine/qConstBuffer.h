#pragma once
#include "qEntity.h"


class qConstBuffer : public qEntity
{
public:
	qConstBuffer();
	~qConstBuffer();

public:
	int Create(CB_TYPE _type, UINT _BufferSize);

	void SetData(void* _pData);
	void Binding();
	void Binding_CS();

	virtual qConstBuffer* Clone() { return nullptr; }

private:
	ComPtr<ID3D11Buffer>		m_CB;
	D3D11_BUFFER_DESC			m_Desc;
	CB_TYPE						m_CBType;


};

