#pragma once
#include "qComputeShader.h"

class qStructuredBuffer;

class qWeightMapCS : public qComputeShader
{
public:
	qWeightMapCS();
	~qWeightMapCS();

public:
	virtual int Binding() override;
	virtual void CalcGroupNum() override;
	virtual void Clear() override;

public:
	void SetBrushPos(qStructuredBuffer* _Buffer) { m_RaycastOut = _Buffer; }
	void SetBrushScale(Vec2 _Scale) { m_BrushScale = _Scale; }
	void SetWeightIdx(int _Idx) { m_WeightIdx = _Idx; }
	void SetWeightMapWidthHeight(UINT _Width, UINT _Height)
	{
		m_WeightMapWidth = (int)_Width;
		m_WeightMapHeight = (int)_Height;
	}
	void SetWeightMap(qStructuredBuffer* _WeightMap) { m_WeightMap = _WeightMap; }
	void SetBrushTex(Ptr<qTexture> _BrushTex) { m_BrushTex = _BrushTex; }




private:
	qStructuredBuffer*		m_WeightMap;
	Ptr<qTexture>			m_BrushTex;
	qStructuredBuffer*		m_RaycastOut;
	Vec2					m_BrushScale;
	int						m_WeightIdx;

	int						m_WeightMapWidth;
	int						m_WeightMapHeight;
};

