#pragma once
#include "qComputeShader.h"

class qStructuredBuffer;

class qHeightMapCS : public qComputeShader
{
public:
	qHeightMapCS();
	~qHeightMapCS();

public:
	virtual int Binding() override;
	virtual void CalcGroupNum() override;
	virtual void Clear() override;


public:
	void SetBrushPos(qStructuredBuffer* _Buffer) { m_RaycastOut = _Buffer; }
	void SetBrushScale(Vec2 _BrushScale) { m_BrushScale = _BrushScale; }

	void SetHeightMap(Ptr<qTexture> _HeightMap) { m_HeightMapTex = _HeightMap; }
	void SetBrushTex(Ptr<qTexture> _BrushTex) { m_BrushTex = _BrushTex; }


private:
	Ptr<qTexture>		m_HeightMapTex;
	Ptr<qTexture>		m_BrushTex;

	qStructuredBuffer*  m_RaycastOut;
	Vec2				m_BrushScale;
};

