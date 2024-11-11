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
	void SetFace(int _X, int _Z);
	void SetHeightMap(Ptr<qTexture> _HeightMap) { m_HeightMap = _HeightMap; }

private:
	void CreateMesh();

private:
	int					m_FaceX;
	int					m_FaceZ;
	Ptr<qTexture>		m_HeightMap;

	float				m_TessLevel;

};

