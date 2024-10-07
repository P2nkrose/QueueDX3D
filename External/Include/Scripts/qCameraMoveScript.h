#pragma once
#include <Engine/qScript.h>

class qCameraMoveScript : public qScript
{
public:
	CLONE(qCameraMoveScript);
	qCameraMoveScript();
	~qCameraMoveScript();
	
	virtual void Begin() override;
	virtual void Tick() override;

public:
	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;

public:
	void SetFollowObject(qGameObject* _Obj) { m_FollowObj = _Obj; }

	void SetClap(bool _clap) { m_clap = _clap; }


private:
	void OrthoGraphicMove();
	void PerspectiveMove();


private:
	float				m_CamSpeed;
	qGameObject*		m_FollowObj;

	bool				m_clap;

	Vec3				fixPos;
};

