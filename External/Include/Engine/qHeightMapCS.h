#pragma once
#include "qComputeShader.h"

class qStructuredBuffer;

struct tRaycastOut
{
	Vec2	Location;
	UINT	Distance;
	int		Success;
};

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
	void SetBrushPos(Vec2 _BrushPos) { m_BrushPos = _BrushPos; }
	void SetBrushScale(Vec2 _BrushScale) { m_BrushScale = _BrushScale; }

	void SetHeightMap(Ptr<qTexture> _HeightMap) { m_HeightMapTex = _HeightMap; }
	void SetBrushTex(Ptr<qTexture> _BrushTex) { m_BrushTex = _BrushTex; }


private:
	Ptr<qTexture>		m_HeightMapTex;
	Ptr<qTexture>		m_BrushTex;

	Vec2				m_BrushPos;
	Vec2				m_BrushScale;
};

