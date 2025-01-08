#pragma once
#include "qAsset.h"

#include "Ptr.h"
#include "qTexture.h"
#include "qGraphicShader.h"

class qMaterial : public qAsset
{
public:
	CLONE(qMaterial);
	qMaterial(bool _IsEngine = false);
	~qMaterial();

public:
	virtual int Save(const wstring& _FilePath) override;
	virtual int Load(const wstring& _FilePath) override;

public:
	void Binding();
	
	void SetShader(Ptr<qGraphicShader> _Shader) { m_Shader = _Shader; }
	Ptr<qGraphicShader> GetShader() { return m_Shader; }


public:
	template<typename T>
	void SetScalarParam(SCALAR_PARAM _Param, const T& _Data);
	void SetTexParam(TEX_PARAM _Param, Ptr<qTexture> _Tex) { m_arrTex[_Param] = _Tex; }

	void* GetScalarParam(SCALAR_PARAM _Param);
	Ptr<qTexture> GetTexParam(TEX_PARAM _Param) { return m_arrTex[(UINT)_Param]; }


public:
	void SetMaterialCoefficient(Vec4 _vDiff, Vec4 _vSpec, Vec4 _vAmb, Vec4 _vEmis)
	{
		m_Const.mtrl.vDiff = _vDiff;
		m_Const.mtrl.vAmb = _vAmb;
		m_Const.mtrl.vSpec = _vSpec;
		m_Const.mtrl.vEmv = _vEmis;
	}

	void SetAnim3D(bool _bTrue) { m_Const.arrAnimData[0] = (int)_bTrue; }
	void SetBoneCount(int _iBoneCount) { m_Const.arrAnimData[1] = _iBoneCount; }

	void operator = (const qMaterial& _OtherMtrl)
	{
		SetName(_OtherMtrl.GetName());

		m_Const = _OtherMtrl.m_Const;

		for (UINT i = 0; i < (UINT)TEX_PARAM::END; ++i)
		{
			m_arrTex[i] = _OtherMtrl.m_arrTex[i];
		}

		m_Shader = _OtherMtrl.m_Shader;
	}



private:
	Ptr<qGraphicShader>			m_Shader;

	tMtrlConst					m_Const;
	Ptr<qTexture>				m_arrTex[TEX_PARAM::END];
};


template<typename T>
void qMaterial::SetScalarParam(SCALAR_PARAM _Param, const T& _Data)
{
	if constexpr (std::is_same_v<T, int>) { m_Const.iArr[_Param] = _Data; return; }
	if constexpr (std::is_same_v<T, float>) { m_Const.fArr[_Param - FLOAT_0] = _Data; return; }
	if constexpr (std::is_same_v<T, Vec2>) { m_Const.v2Arr[_Param - VEC2_0] = _Data; return; }
	if constexpr (std::is_same_v<T, Vec4> || std::is_same_v<T, Vec3>) { m_Const.v4Arr[_Param - VEC4_0] = _Data; return; }
	if constexpr (std::is_same_v<T, Matrix>) { m_Const.matArr[_Param - MAT_0] = _Data; return; }

	assert(nullptr);
}