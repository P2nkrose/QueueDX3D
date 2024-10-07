#pragma once
#include "qAsset.h"

class qShader : public qAsset
{
public:
	qShader(ASSET_TYPE _Type);
	~qShader();


public:
	virtual int Load(const wstring& _FilePath) { return S_OK; }
	virtual int Save(const wstring& _FilePath) { return S_OK; }


protected:
	ComPtr<ID3DBlob>	m_ErrBlob;
};

