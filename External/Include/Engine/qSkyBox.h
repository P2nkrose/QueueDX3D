#pragma once
#include "qRenderComponent.h"

enum SKYBOX_TYPE
{
	SPHERE,
	CUBE,
};

class qSkyBox : public qRenderComponent
{
public:
	CLONE(qSkyBox);
	qSkyBox();
	~qSkyBox();

public:
	virtual void FinalTick() override;
	virtual void Render() override;

	virtual void SaveToFile(FILE* _File) override;   // ���Ͽ� ������Ʈ�� ������ ����
	virtual void LoadFromFile(FILE* _File) override; // ���Ͽ� ������Ʈ�� ������ �ε�


public:
	void SetSkyBoxType(SKYBOX_TYPE _Type);
	void SetSkyBoxTexture(Ptr<qTexture> _Tex) { m_SkyBoxTex = _Tex; }



private:
	SKYBOX_TYPE     m_Type;
	Ptr<qTexture>   m_SkyBoxTex;
};
