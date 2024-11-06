#pragma once
#include "qRenderComponent.h"

class qLandScape : public qRenderComponent
{
public:
	CLONE(qLandScape);
	qLandScape();
	~qLandScape();

public:
	virtual void FinalTick() override;
	virtual void Render() override;
	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;

public:
	void SetFace(UINT _X, UINT _Z);

private:
	void CreateMesh();

private:
	UINT			m_FaceX;
	UINT			m_FaceZ;
};

