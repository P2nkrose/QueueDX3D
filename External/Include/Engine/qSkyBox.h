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
	qSkyBox(const qSkyBox& _Origin);
	~qSkyBox();

public:
	virtual void FinalTick() override;
	virtual void Render() override;
	virtual void render_shadowmap() override;

	virtual void SaveToFile(FILE* _File) override;   // ���Ͽ� ������Ʈ�� ������ ����
	virtual void LoadFromFile(FILE* _File) override; // ���Ͽ� ������Ʈ�� ������ �ε�


public:
	void SetSkyBoxType(SKYBOX_TYPE _Type);
	void SetSkyBoxTexture(Ptr<qTexture> _Tex) { m_SkyBoxTex = _Tex; }

	SKYBOX_TYPE GetSkyBoxType() { return m_Type; }
	Ptr<qTexture> GetSkyBoxTexture() { return m_SkyBoxTex; }

private:
	SKYBOX_TYPE     m_Type;
	Ptr<qTexture>   m_SkyBoxTex;
};

