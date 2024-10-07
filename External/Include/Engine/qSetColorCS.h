#pragma once
#include "qComputeShader.h"

class qSetColorCS : public qComputeShader
{
public:
	qSetColorCS();
	~qSetColorCS();

public:
	virtual int Binding() override;
	virtual void CalcGroupNum() override;
	virtual void Clear() override;

public:
	void SetTargetTexture(Ptr<qTexture> _Tex) { m_TargetTex = _Tex; }
	void SetClearColor(Vec4 _Color) { m_ClearColor = _Color; }
	

private:
	Ptr<qTexture>		m_TargetTex;
	Vec4				m_ClearColor;
};

