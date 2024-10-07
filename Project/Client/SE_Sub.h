#pragma once
#include "EditorUI.h"

#include "SpriteEditor.h"
#include <Engine/qAssetMgr.h>

class SE_Sub : public EditorUI
{
	friend class SpriteEditor;

public:
	SE_Sub();
	~SE_Sub();

public:
	SpriteEditor* GetOwner() { return m_Owner; }
	class SE_Detail* GetDetail() { return m_Owner->GetDetail(); }
	class SE_AtlasView* GetAtlasView() { return m_Owner->GetAtlasView(); }


private:
	SpriteEditor* m_Owner;
};

