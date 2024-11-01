#pragma once
#include "qComponent.h"

class qLight3D : public qComponent
{
public:
	CLONE(qLight3D);
	qLight3D();
	qLight3D(const qLight3D& _Origin);
	~qLight3D();

public:
	virtual void FinalTick() override;
	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;


public:
    void Render();
    void CreateShadowMap();

public:
    void SetLightType(LIGHT_TYPE _Type);
    void SetRadius(float _Radius);
    void SetAngle(float _Angle) { m_Info.Angle = _Angle; }
    void SetLightColor(Vec3 _Color) { m_Info.light.Color = _Color; }
    void SetLightAmbient(Vec3 _Amb) { m_Info.light.Ambient = _Amb; }
    void SetSpecularCoefficient(float _Coef) { m_Info.light.SpecCoef = _Coef; }

    LIGHT_TYPE GetLightType() { return m_Info.Type; }
    float GetRadius() { return m_Info.Radius; }
    float GetAngle() { return m_Info.Angle; }
    Vec3 GetLightColor() { return m_Info.light.Color; }
    Vec3 GetLightAmbient() { return m_Info.light.Ambient; }


    const tLightInfo& GetLightInfo() { return m_Info; }


private:
	tLightInfo		    m_Info;
    int                 m_LightIdx;

    Ptr<qMesh>          m_VolumeMesh;
    Ptr<qMaterial>      m_LightMtrl;

    // ShadowMap MRT
    class qMRT*         m_ShadowMapMRT;

    // ShadowMap 재질
    Ptr<qMaterial>      m_ShadowMapMtrl;

    // 광원이 보유한 카메라
    qGameObject*        m_Cam;

    // 타겟 포지션
    Vec3                m_TargetPos;
};

