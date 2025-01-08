#pragma once
#include "qComputeShader.h"

class qStructuredBuffer;

class qAnimation3DShader : public qComputeShader
{
public:
	qAnimation3DShader();
	~qAnimation3DShader();

public:
	virtual int Binding() override;
	virtual void CalcGroupNum() override;
	virtual void Clear() override;

public:
    // g_int_0 : BonCount, g_int_1 : Frame Index
    void SetBoneCount(int _iBoneCount) { m_Const.iArr[0] = _iBoneCount; }
    void SetFrameIndex(int _iFrameIdx) { m_Const.iArr[1] = _iFrameIdx; }
    void SetNextFrameIdx(int _iFrameIdx) { m_Const.iArr[2] = _iFrameIdx; }
    void SetFrameRatio(float _fFrameRatio) { m_Const.fArr[0] = _fFrameRatio; }
    void SetFrameDataBuffer(qStructuredBuffer* _buffer) { m_pFrameDataBuffer = _buffer; }
    void SetOffsetMatBuffer(qStructuredBuffer* _buffer) { m_pOffsetMatBuffer = _buffer; }
    void SetOutputBuffer(qStructuredBuffer* _buffer) { m_pOutputBuffer = _buffer; }


private:
    qStructuredBuffer*  m_pFrameDataBuffer;			// t16
    qStructuredBuffer*  m_pOffsetMatBuffer;			// t17 
    qStructuredBuffer*  m_pOutputBuffer;		    // u0
};

