#pragma once
#include "ComponentUI.h"

class MeshRenderUI : public ComponentUI
{
public:
	MeshRenderUI();
	~MeshRenderUI();

public:
	void SelectMesh(DWORD_PTR _ListUI);
	void SelectMaterial(DWORD_PTR _ListUI);

private:
	virtual void Update() override;



};

