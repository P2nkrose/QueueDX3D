#pragma once
#include "qComputeShader.h"

class qStructuredBuffer;

class qParticleTickCS : public qComputeShader
{
public:
	qParticleTickCS();
	~qParticleTickCS();

public:
	virtual int Binding() override;
	virtual void CalcGroupNum() override;
	virtual void Clear() override;

public:
	void SetParticleBuffer(qStructuredBuffer* _Buffer) { m_ParticleBuffer = _Buffer; }
	void SetSpawnCount(qStructuredBuffer* _Buffer) { m_SpawnCountBuffer = _Buffer; }
	void SetModuleBuffer(qStructuredBuffer* _ModuleBuffer) { m_ModuleBuffer = _ModuleBuffer; }

	void SetParticleWorldPos(Vec3 _Pos) { m_ParticleWorldPos = _Pos; }
	void SetNoiseTexture(Ptr<qTexture> _Noise) { m_NoiseTex = _Noise; }

private:
	qStructuredBuffer*		m_ParticleBuffer;
	qStructuredBuffer*		m_SpawnCountBuffer;
	qStructuredBuffer*		m_ModuleBuffer;

	Ptr<qTexture>			m_NoiseTex;
	Vec3					m_ParticleWorldPos;

};

