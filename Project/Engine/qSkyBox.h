#pragma once
#include "qRenderComponent.h"

class qSkyBox : public qRenderComponent
{
public:
	CLONE(qSkyBox);
	qSkyBox();
	~qSkyBox();

public:
	virtual void FinalTick() override;
	virtual void Render() override;

	virtual void SaveToFile(FILE* _File) override;   // 파일에 컴포넌트의 정보를 저장
	virtual void LoadFromFile(FILE* _File) override; // 파일에 컴포넌트의 정보를 로드

private:

};

