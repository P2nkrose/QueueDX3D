#pragma once
#include "EditorUI.h"

class SE_AtlasView;
class SE_Detail;

class SpriteEditor : public EditorUI
{
public:
	SpriteEditor();
	~SpriteEditor();

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	virtual void Activate() override;
	virtual void Deactivate() override;

public:
	SE_AtlasView* GetAtlasView() { return m_AtlasView; }
	SE_Detail* GetDetail() { return m_Detail; }


private:
	SE_AtlasView*		m_AtlasView;
	SE_Detail*			m_Detail;
};

