#pragma once
#include "qShader.h"

struct tScalarParam
{
	SCALAR_PARAM	ParamType;
	string			strDesc;
};


struct tTexParam
{
	TEX_PARAM		ParamType;
	string			strDesc;
};


class qGraphicShader : public qShader
{
public:
	qGraphicShader();
	~qGraphicShader();


public:
	int CreateVertexShader(const wstring& _RelativePath, const string& _FuncName);
	int CreateHullShader(const wstring& _RelativePath, const string& _FuncName);
	int CreateDomainShader(const wstring& _RelativePath, const string& _FuncName);
	int CreateGeometryShader(const wstring& _RelativePath, const string& _FuncName);
	int CreatePixelShader(const wstring& _RelativePath, const string& _FuncName);

	void Binding();


public:
	void SetDomain(SHADER_DOMAIN _Domain) { m_Domain = _Domain; }

	void SetTopology(D3D11_PRIMITIVE_TOPOLOGY _Topology) { m_Topology = _Topology; }

	void SetRSType(RS_TYPE _Type) { m_RSType = _Type; }
	void SetDSType(DS_TYPE _Type) { m_DSType = _Type; }
	void SetBSType(BS_TYPE _Type) { m_BSType = _Type; }

	// shader parameter
	void AddScalarParam(SCALAR_PARAM _Type, const string& _Desc) { m_ScalarParam.push_back(tScalarParam{ _Type, _Desc }); }
	void AddTexParam(TEX_PARAM _Type, const string& _Desc)	{ m_TexParam.push_back(tTexParam{ _Type, _Desc }); }
	
	const vector<tScalarParam>& GetScalarParam() { return m_ScalarParam; }
	const vector<tTexParam>& GetTexParam() { return m_TexParam; }

	SHADER_DOMAIN GetDomain() { return m_Domain; }
	RS_TYPE GetRSType() { return m_RSType; }
	DS_TYPE GetDSType() { return m_DSType; }
	BS_TYPE GetBSType() { return m_BSType; }


private:
	// πˆ≈ÿΩ∫ Ω¶¿Ã¥ı (Vertex Shader)
	ComPtr<ID3DBlob>				m_VSBlob;
	ComPtr<ID3D11VertexShader>		m_VS;
									
	// «»ºø Ω¶¿Ã¥ı (Pixel Shader)	
	ComPtr<ID3DBlob>				m_PSBlob;
	ComPtr<ID3D11PixelShader>		m_PS;

	// ¡ˆø¿∏ﬁ∆Æ∏Æ Ω¶¿Ã¥ı (Geometry Shader)
	ComPtr<ID3DBlob>				m_GSBlob;
	ComPtr<ID3D11GeometryShader>	m_GS;

	// «Ê Ω¶¿Ã¥ı (Hull Shader)
	ComPtr<ID3DBlob>			    m_HSBlob;
	ComPtr<ID3D11HullShader>        m_HS;

	// µµ∏ﬁ¿Œ Ω¶¿Ã¥ı (Domain Shader)
	ComPtr<ID3DBlob>			    m_DSBlob;
	ComPtr<ID3D11DomainShader>      m_DS;

	ComPtr<ID3D11InputLayout>		m_Layout;

	D3D11_PRIMITIVE_TOPOLOGY		m_Topology;

	RS_TYPE							m_RSType;
	DS_TYPE							m_DSType;
	BS_TYPE							m_BSType;


	SHADER_DOMAIN					m_Domain;		// Ω¶¿Ã¥ı¿« ∑ª¥ı∏µ πÊΩƒ


	// Shader Parameter
	vector<tScalarParam>			m_ScalarParam;
	vector<tTexParam>				m_TexParam;

};

