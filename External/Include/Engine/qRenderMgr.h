#pragma once
#include "singleton.h"

class qCamera;
class qGameObject;
class qLight2D;
class qLight3D;
class qStructuredBuffer;
class qMRT;

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
	int  RegisterLight3D(qLight3D* _Light) { m_vecLight3D.push_back(_Light); return m_vecLight3D.size() - 1; }

	void PostProcessCopy();

	void SetSpecifiedTarget(Ptr<qTexture> _TargetTex) { m_SpecfiedTarget = _TargetTex; }
	Ptr<qTexture> GetSpecifiedTarget() { return m_SpecfiedTarget; }

	qMRT* GetMRT(MRT_TYPE _Type) { return m_arrMRT[(UINT)_Type]; }

	qCamera* GetPOVCam();

private:
	void RenderStart();
	void Render(qCamera* _Cam);
	void Render_Sub(qCamera* _Cam);

	void Clear();
	void RenderDebugShape();
	void CreateMRT();
	void ClearMRT();
	void CreateMaterial();

private:
	vector<qCamera*>			m_vecCam;
	qCamera*					m_EditorCamera;

	qGameObject*				m_DebugObject;
	list<tDebugShapeInfo>		m_DebugShapeList;

	// Light
	vector<qLight2D*>			m_vecLight2D;
	qStructuredBuffer*			m_Light2DBuffer;


	// Light
	vector<qLight3D*>			m_vecLight3D;
	qStructuredBuffer*			m_Light3DBuffer;


	// Post Process
	Ptr<qTexture>				m_PostProcessTex;

	// Down Scale
	Ptr<qTexture>				m_DownScaleTex;

	// MRT
	qMRT*						m_arrMRT[(UINT)MRT_TYPE::END];

	// ∫¥«’ Ω¶¿Ã¥ı
	Ptr<qMesh>					m_RectMesh;
	Ptr<qMaterial>				m_MergeMtrl;
	Ptr<qTexture>				m_SpecfiedTarget;
};

