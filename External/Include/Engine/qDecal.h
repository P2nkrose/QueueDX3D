#pragma once
#include "qRenderComponent.h"

class qDecal : public qRenderComponent
{
public:
	CLONE(qDecal);
	qDecal();
	~qDecal();

public:
	virtual void FinalTick() override;
	virtual void Render() override;

	virtual void SaveToFile(FILE* _File) override;   // 파일에 컴포넌트의 정보를 저장
	virtual void LoadFromFile(FILE* _File) override; // 파일에 컴포넌트의 정보를 로드

public:
	void SetDecalTexture(Ptr<qTexture> _Tex) { m_DecalTex = _Tex; }
	void SetEmissiveTexture(Ptr<qTexture> _Tex) { m_EmissiveTex = _Tex; }


private:
	Ptr<qTexture>		m_DecalTex;
	Ptr<qTexture>		m_EmissiveTex;
};

