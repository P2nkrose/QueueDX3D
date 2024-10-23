#pragma once
#include "qComponent.h"

class qGameObject;

enum PROJ_TYPE
{
	ORTHOGRAPHIC,
	PERSPECTIVE,
};


class qCamera : public qComponent
{
public:
	friend class qRenderMgr;

	CLONE(qCamera);
	qCamera();
	~qCamera();

public:
	virtual void Begin() override;
	virtual void FinalTick() override;
	void Render();


public:
	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;
	int GetPriority() { return m_Priority; }


public:
	void SetPriority(int _Priority) { m_Priority = _Priority; }
	void SetLayer(UINT _LayerIdx, bool _bCheck)
	{
		if (_bCheck)
			m_LayerCheck |= (1 << _LayerIdx);
		else
			m_LayerCheck &= ~(1 << _LayerIdx);
	}
	void SetLayerAll() { m_LayerCheck = 0xffffffff; }

	bool GetLayerCheck(UINT _LayerIdx) { return m_LayerCheck & (1 << _LayerIdx); }
	
	void SetProjType(PROJ_TYPE _Type) { m_ProjType = _Type; }
	PROJ_TYPE GetProjType() { return m_ProjType; }

	void SetWidth(float _Width)
	{
		m_Width = _Width;
		m_AspectRatio = m_Width / m_Height;
	}

	void SetHeight(float _Height)
	{
		m_Height = _Height;
		m_AspectRatio = m_Width / m_Height;
	}

	float GetWidth() { return m_Width; }
	float GetHeight() { return m_Height; }
	float GetAspectRatio() { return m_AspectRatio; }


	void SetFar(float _Far) { m_Far = _Far; }
	float GetFar() { return m_Far; }

	void SetFOV(float _FOV) { m_FOV = _FOV; }
	float GetFOV() { return m_FOV; }

	void SetScale(float _Scale) { m_ProjectionScale = _Scale; }
	float GetScale() { return m_ProjectionScale; }

	const Matrix& GetViewMat() { return m_matView; }
	const Matrix& GetViewMatInv() { return m_matViewInv; }
	const Matrix& GetProjMat() { return m_matProj; }
	const Matrix& GetProjMatInv() { return m_matProjInv; }

private:
	void SortGameObject();

	void render_deferred();

	void render_opaque();
	void render_masked();
	void render_effect();
	void render_transparent();
	void render_particle();
	void render_postprocess();
	void render_ui();

	void clear();


private:
	int						m_Priority;				// 우선순위
	UINT					m_LayerCheck;			// 원하는 레이어만 카메라에 찍히도록 설정

	PROJ_TYPE				m_ProjType;

	float					m_Width;
	float					m_Height;
	float					m_AspectRatio;			// 종횡 비
	float					m_Far;					// 카메라가 볼수 있는 시야 거리 (ex : 10000.f)
	float					m_FOV;					// Field Of View (시야 범위, 시야 각)
	float					m_ProjectionScale;

	Matrix                  m_matView;
	Matrix                  m_matViewInv;
	Matrix                  m_matProj;
	Matrix                  m_matProjInv;
	
	vector<qGameObject*>	m_vecDeferred;			// Deferred
	vector<qGameObject*>	m_vecOpaque;			// 불투명
	vector<qGameObject*>	m_vecMasked;			// 불투명, 투명
	vector<qGameObject*>	m_vecTransparent;		// 투명, 반투명
	vector<qGameObject*>    m_vecEffect;
	vector<qGameObject*>	m_vecParticles;			// 투명, 반투명, 입자 타입
	vector<qGameObject*>	m_vecPostProcess;		// 후처리 오브젝트

	vector<qGameObject*>	m_vecUI;				// UI 오브젝트

};

