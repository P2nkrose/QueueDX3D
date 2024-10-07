#pragma once
#include "qScript.h"

class qCameraMoveScript : public qScript
{
public:
	CLONE(qCameraMoveScript);
	qCameraMoveScript();
	~qCameraMoveScript();

	virtual void Tick() override;


private:
	void OrthoGraphicMove();
	void PerspectiveMove();


private:
	float		m_CamSpeed;
};

