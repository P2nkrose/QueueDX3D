#include "pch.h"
#include "qAnimation3DShader.h"

#include "qStructuredBuffer.h"

qAnimation3DShader::qAnimation3DShader()
    : qComputeShader(256, 1, 1, L"shader\\animation.fx", "CS_Animation3D")
    , m_pFrameDataBuffer(nullptr)
    , m_pOffsetMatBuffer(nullptr)
    , m_pOutputBuffer(nullptr)
{
}

qAnimation3DShader::~qAnimation3DShader()
{
}

int qAnimation3DShader::Binding()
{
    // ����ȭ���� ����
    m_pFrameDataBuffer->Binding_CS_SRV(16); // t16
    m_pOffsetMatBuffer->Binding_CS_SRV(17); // t17
    m_pOutputBuffer->Binding_CS_UAV(0);   // u0

    return S_OK;
}

void qAnimation3DShader::CalcGroupNum()
{
    UINT GroupX = (m_Const.iArr[0] / m_ThreadPerGroupX) + 1;
    UINT GroupY = 1;
    UINT GroupZ = 1;
}

void qAnimation3DShader::Clear()
{
    m_pFrameDataBuffer->Clear_CS_SRV();
    m_pOffsetMatBuffer->Clear_CS_SRV();
    m_pOutputBuffer->Clear_CS_UAV();

    m_pFrameDataBuffer = nullptr;
    m_pOffsetMatBuffer = nullptr;
    m_pOutputBuffer = nullptr;
}
