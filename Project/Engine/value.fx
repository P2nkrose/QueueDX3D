#ifndef _VALUE
#define _VALUE

#include "struct.fx"

#define PI 3.1415926535f

// 4096
cbuffer OBJECT_POS : register(b0)
{
    row_major matrix matWorld;
    row_major matrix matView;
    row_major matrix matProj;
    
    row_major matrix matWorldInv;
    row_major matrix matViewInv;
    row_major matrix matProjInv;
    
    
    row_major matrix matWV;
    row_major matrix matWVP;
};

cbuffer MATERIAL : register(b1)
{
    // 재질 계수
    float4 g_vDiff;
    float4 g_vSpec;
    float4 g_vAmb;
    float4 g_vEmv;
    
    int g_int_0;
    int g_int_1;
    int g_int_2;
    int g_int_3;
    
    float g_float_0;
    float g_float_1;
    float g_float_2;
    float g_float_3;
    
    float2 g_vec2_0;
    float2 g_vec2_1;
    float2 g_vec2_2;
    float2 g_vec2_3;
    
    float4 g_vec4_0;
    float4 g_vec4_1;
    float4 g_vec4_2;
    float4 g_vec4_3;
    
    row_major matrix g_mat_0;
    row_major matrix g_mat_1;
    row_major matrix g_mat_2;
    row_major matrix g_mat_3;
    
    int g_btex_0;
    int g_btex_1;
    int g_btex_2;
    int g_btex_3;
    int g_btex_4;
    int g_btex_5;
    int g_btexcube_0;
    int g_btexcube_1;
    int g_btexarr_0;
    int g_btexarr_1;
    
    // 3D Animation 정보
    int g_iAnim;
    int g_iBoneCount;
}


cbuffer SPRITE_INFO : register(b2)
{
    float2  LeftTopUV;
    float2  SliceUV;
    float2  BackGroundUV;
    float2  OffsetUV;
    int     UseFlipbook;
    int3    SpriteInfoPadding;
}


cbuffer GLOBAL_DATA : register(b3)
{
    // 시간 관련 정보
    float   g_DT;
    float   g_EngineDT;
    float   g_Time;
    float   g_EngineTime;
    
    // 랜더링을 할 때의 카메라 (시점) 의 월드 위치
    float4 g_CamWorldPos;
    
    // 랜더타겟의 해상도 정보
    float2  g_Resolution;

    // 바인딩 된 구조화버퍼에 광원이 몇개 들어있느지
    int     g_Light2DCount;
    int     g_Light3DCount;
}


cbuffer HUD : register(b4)
{
    float   HPRatio;
    float   Padding1;
    float   Padding2;
    float   Padding3;
}

cbuffer BOSSHUD : register(b5)
{
    float   BOSSHPRatio;
    float   bossPadding1;
    float   bossPadding2;
    float   bossPadding3;
}



SamplerState g_sam_0 : register(s0); // 이방성 필터 샘플러
SamplerState g_sam_1 : register(s1); // 포인트 필터 샘플러
SamplerState g_sam_2 : register(s2); // 선형 필터 샘플러


Texture2D       g_tex_0 : register(t0);
Texture2D       g_tex_1 : register(t1);
Texture2D       g_tex_2 : register(t2);
Texture2D       g_tex_3 : register(t3);
Texture2D       g_tex_4 : register(t4);
Texture2D       g_tex_5 : register(t5);
TextureCube     g_texcube_0 : register(t6);
TextureCube     g_texcube_1 : register(t7);
Texture2DArray  g_texarr_0 : register(t8);
Texture2DArray  g_texarr_1 : register(t9);

Texture2D       g_AtlasTex : register(t10);     // 애니메이션 전용 스프라이트가 있는 아틀라스


StructuredBuffer<tLightInfo> g_Light2D : register(t11);
StructuredBuffer<tLightInfo> g_Light3D : register(t12);


// Animation3D Bone Matrix Buffer
StructuredBuffer<Matrix> g_arrBoneMat : register(t17);

#endif
