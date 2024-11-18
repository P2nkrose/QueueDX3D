#pragma once
#include "qComputeShader.h"

class qStructuredBuffer;

class qRaycastCS : public qComputeShader
{
public:
	qRaycastCS();
	~qRaycastCS();

public:
	virtual int Binding() override;
	virtual void CalcGroupNum()override;
	virtual void Clear() override;

public:
	void SetHeightMap(Ptr<qTexture> _HeightMap) { m_HeightMap = _HeightMap; }
	void SetRayInfo(const tRay& _ray) { m_Ray = _ray; }
	void SetFace(UINT _FaceX, UINT _FaceZ) { m_FaceX = _FaceX, m_FaceZ = _FaceZ; }
	void SetOutBuffer(qStructuredBuffer* _Buffer) { m_OutBuffer = _Buffer; }

private:
	UINT					m_FaceX;
	UINT					m_FaceZ;
	tRay					m_Ray;

	Ptr<qTexture>			m_HeightMap;
	qStructuredBuffer*		m_OutBuffer;
};

