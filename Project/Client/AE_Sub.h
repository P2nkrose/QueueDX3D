#pragma once
#include "EditorUI.h"

#include "AnimationEditor.h"
#include <Engine/qAssetMgr.h>

class AE_Sub : public EditorUI
{
public:
	friend class AnimationEditor;

	AE_Sub();
	~AE_Sub();

public:
	AnimationEditor* GetOwner() { return m_Owner; }


	class AE_Detail* GetDetail() { return m_Owner->GetDetail(); }
	class AE_Preview* GetPreview() { return m_Owner->GetPreview(); }
	class AE_SpriteList* GetSpriteList() { return m_Owner->GetSpriteList(); }


private:
	AnimationEditor* m_Owner;
};

