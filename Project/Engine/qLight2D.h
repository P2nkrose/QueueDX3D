#pragma once
#include "qComponent.h"

class qLight2D : public qComponent
{
public:
	CLONE(qLight2D);
	qLight2D();
	~qLight2D();

public:
	virtual void FinalTick() override;

public:
	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;


public:
	void SetLightType(LIGHT_TYPE _Type);
	void SetRadius(float _Radius) { m_Info.Radius = _Radius; }
	void SetAngle(float _Angle) { m_Info.Angle = _Angle; }
	void SetLightColor(Vec3 _Color) { m_Info.light.Color = _Color; }
	void SetLightAmbient(Vec3 _Amb) { m_Info.light.Ambient = _Amb; }

	LIGHT_TYPE GetLightType() { return m_Info.Type; }
	float GetRadius() { return m_Info.Radius; }
	float GetAngle() { return m_Info.Angle; }
	Vec3 GetLightColor() { return m_Info.light.Color; }
	Vec3 GetLightAmbient() { return m_Info.light.Ambient; }

	const tLightInfo& GetLightInfo() { return m_Info; }


private:
	tLightInfo		m_Info;
};

