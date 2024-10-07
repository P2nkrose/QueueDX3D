#pragma once
#include "singleton.h"

class qCamera;
class qGameObject;
class qLight2D;
class qStructuredBuffer;

class qRenderMgr : public qSingleton<qRenderMgr>
{
	SINGLE(qRenderMgr)

public:
	void Init();
	void Tick();

	void RegisterCamera(qCamera* _Cam, int _CamPriority);
	void RegisterEditorCamera(qCamera* _Cam) { m_EditorCamera = _Cam; }
	void AddDebugShapeInfo(const tDebugShapeInfo& _Info) { m_DebugShapeList.push_back(_Info); }
	void RegisterLight2D(qLight2D* _Light) { m_vecLight2D.push_back(_Light); }

	void PostProcessCopy();

private:
	void RenderStart();
	void Clear();

	void RenderDebugShape();


private:
	vector<qCamera*>			m_vecCam;
	qCamera*					m_EditorCamera;

	qGameObject*				m_DebugObject;
	list<tDebugShapeInfo>		m_DebugShapeList;

	// Light
	vector<qLight2D*>			m_vecLight2D;
	qStructuredBuffer*			m_Light2DBuffer;

	// Post Process
	Ptr<qTexture>				m_PostProcessTex;

	// Down Scale
	Ptr<qTexture>				m_DownScaleTex;
};

