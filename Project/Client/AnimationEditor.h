#pragma once
#include "EditorUI.h"

class AE_Detail;
class AE_Preview;
class AE_SpriteList;

class AnimationEditor : public EditorUI
{
public:
	AnimationEditor();
	~AnimationEditor();

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	virtual void Activate() override;
	virtual void Deactivate() override;

public:
	AE_Preview* GetPreview() { return m_Preview; }
	AE_SpriteList* GetSpriteList() { return m_SpriteList; }
	AE_Detail* GetDetail() { return m_Detail; }

	
private:
	void Window();

	wstring GetAssetKey(ASSET_TYPE _Type, const wstring& _Format);

	
private:
	AE_Preview*			m_Preview;
	AE_Detail*			m_Detail;
	AE_SpriteList*		m_SpriteList;


};

