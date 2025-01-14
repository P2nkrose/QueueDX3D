#ifndef _MERGE
#define _MERGE

#include "value.fx"

// ================================
// MergeShader
// MRT : SwapChain
// Mesh : RectMesh
// Rasterizer : CULL_BACK
// DepthStencil : NO_TEST_NO_WRITE
// BlendState   : Default
// Parameter
#define MERGE_MODE          g_int_0

#define ALBEDO_TARGET       g_tex_0
#define DIFFUSE_TARGET      g_tex_1
#define SPECULAR_TARGET     g_tex_2
#define EMISSIVE_TARGET     g_tex_3

#define SPECIFIED_TARGET    g_tex_4
// =================================
struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};

VS_OUT VS_Merge(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
        
    output.vPosition = float4(_in.vPos * 2.f, 1.f);
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_Merge(VS_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;

    if (0 == MERGE_MODE)
    {
        float4 vColor = ALBEDO_TARGET.Sample(g_sam_0, _in.vUV);
        float4 vDiffuse = DIFFUSE_TARGET.Sample(g_sam_0, _in.vUV);
        float4 vSpecular = SPECULAR_TARGET.Sample(g_sam_0, _in.vUV);
        float4 vEmissive = EMISSIVE_TARGET.Sample(g_sam_0, _in.vUV);
        vOutColor = vColor * vDiffuse + vSpecular + vEmissive;
    }
    else if (1 == MERGE_MODE)
    {
        vOutColor = SPECIFIED_TARGET.Sample(g_sam_0, _in.vUV);
    }
    
    return vOutColor;
}





#endif