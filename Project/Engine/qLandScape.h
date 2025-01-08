#pragma once
#include "qRenderComponent.h"

#include "qRaycastCS.h"
#include "qHeightMapCS.h"
#include "qWeightMapCS.h"

struct tRaycastOut
{
	Vec2    Location;
	UINT    Distance;
	int     Success;
};

enum LANDSCAPE_MODE
{
	NONE,
	HEIGHTMAP,
	SPLATING,
};

struct tWeight8
{
	float arrWeight[8];
};

class qLandScape : public qRenderComponent
{
public:
	CLONE(qLandScape);
	qLandScape();
	~qLandScape();

public:
	virtual void Init() override;
	virtual void FinalTick() override;
	virtual void Render() override;
	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;

public:
	void SetFace(int _X, int _Z);
	void AddBrushTexture(Ptr<qTexture> _BrushTex) { m_vecBrush.push_back(_BrushTex); }
	void SetHeightMap(Ptr<qTexture> _HeightMap) { m_HeightMap = _HeightMap; m_IsHeightMapCreated = false; }
	void CreateHeightMap(UINT _Width, UINT _Height);

public:
	int GetFaceX() { return m_FaceX; }
	int GetFaceZ() { return m_FaceZ; }
	
	LANDSCAPE_MODE GetMode() { return m_Mode; }
	void SetMode(LANDSCAPE_MODE _mode) { m_Mode = _mode; }

	Vec2 GetBrushScale() { return m_BrushScale; }
	void SetBrushScale(Vec2 _BrushScale) { m_BrushScale = _BrushScale; }

	int GetWeightIndex() { return m_WeightIdx; }
	void SetWeightIndex(int _wi) { m_WeightIdx = _wi; }

	Ptr<qTexture> GetHeightMap() { return m_HeightMap; }
	Ptr<qTexture> GetBrushTex() { return m_vecBrush[m_BrushIdx]; }

	void SetBrushIndex(Ptr<qTexture> _tex) { m_vecBrush[m_BrushIdx] = _tex; }

private:
	void CreateMesh();
	void CreateComputeShader();
	void CreateTextureAndStructuredBuffer();
	int Raycasting();

private:
	int							m_FaceX;
	int							m_FaceZ;

	// Tessellation
	float						m_MinLevel;
	float						m_MaxLevel;
	float						m_MaxLevelRange;
	float						m_MinLevelRange;

	// Brush
	Vec2						m_BrushScale;
	vector<Ptr<qTexture>>		m_vecBrush;
	UINT						m_BrushIdx;

	// Raycasting
	Ptr<qRaycastCS>				m_RaycastCS;
	qStructuredBuffer*			m_RaycastOut;
	tRaycastOut					m_Out;

	// HeightMap
	Ptr<qTexture>				m_HeightMap;
	bool						m_IsHeightMapCreated;
	Ptr<qHeightMapCS>			m_HeightMapCS;

	// WeightMap
	Ptr<qTexture>				m_ColorTex;
	Ptr<qTexture>				m_NormalTex;
	qStructuredBuffer*			m_WeightMap;
	UINT						m_WeightWidth;
	UINT						m_WeightHeight;
	Ptr<qWeightMapCS>			m_WeightMapCS;
	int							m_WeightIdx;

	// LandScape ¸ðµå
	LANDSCAPE_MODE				m_Mode;

};

