#ifndef _DEBUG_SHADER
#define _DEBUG_SHADER

#include "value.fx"


struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
    
    float3 vNormal : NORMAL;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
    
    float3 vViewPos : POSITION;
    float3 vViewNormal : NORMAL;
};

VS_OUT VS_DebugShape(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
        
    output.vPosition = mul(float4(_in.vPos, 1.f), matWVP);
    output.vUV = _in.vUV;
    
    output.vViewPos = mul(float4(_in.vPos, 1.f), matWV).xyz;
    output.vViewNormal = normalize(mul(float4(_in.vNormal, 0.f), matWV).xyz);
    
    return output;
}

float4 PS_DebugShape(VS_OUT _in) : SV_Target
{
    float4 vColor = g_vec4_0;
    
    if (4 == g_int_0)
    {
        float3 vEye = normalize(_in.vViewPos);
        float Alpha = pow(1.f - saturate(dot(vEye, _in.vViewNormal)), 3);
        vColor.a = Alpha;
    }
    
    return vColor;
}

#endif