#pragma once
#include "qEntity.h"

enum class FACE_TYPE
{
    FT_NEAR,
    FT_FAR,
    FT_TOP,
    FT_BOT,
    FT_LEFT,
    FT_RIGHT,

    END,
};

class qCamera;

class qFrustum : public qEntity
{
public:
	CLONE(qFrustum);
    qFrustum(qCamera* _Owner);
    ~qFrustum();

public:
    void FinalTick();
    bool FrustumCheck(Vec3 _WorldPos, float _Radius = 0.f);


private:
    qCamera*    m_Owner;

    // NDC 좌표계에서 시야의 최대위치 좌표
    Vec3        m_arrProj[8];

    // 절두체를 구성하는 6개의 평면(월드 스페이스 기준)
    Vec4        m_arrFace[(UINT)FACE_TYPE::END];
};

