#pragma once
#include "ComponentUI.h"

#include <Engine/qFlipBookComponent.h>

class FlipBookComUI : public ComponentUI
{
public:
	FlipBookComUI();
	~FlipBookComUI();

public:
	UINT GetUIHeight() { return m_UIHeight; }

private:
	virtual void Update() override;

private:
	void SelectFlipBook(DWORD_PTR _AssetName);
	void ShowFlipBookSprite(Ptr<qFlipBook> _CurFlipBook, int _CurIndex);


private:
	qFlipBookComponent*				m_FBCom;
	Ptr<qFlipBook>					m_CurFB;
	Ptr<qSprite>					m_CurSprite;

	UINT							m_UIHeight;
	
	float							m_AccTime;
	UINT							m_CurSpriteIndex;
	UINT							m_MaxSpriteIndex;
	bool							m_Repeat;
	bool							m_Playing;
};

