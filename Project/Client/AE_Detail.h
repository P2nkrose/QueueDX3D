#pragma once
#include "AE_Sub.h"

#include "ListUI.h"

class AE_Detail : public AE_Sub
{
public:
	friend class AE_Preivew;
	friend class AE_SpriteList;

	AE_Detail();
	~AE_Detail();

public:
	virtual void Init() override;
	virtual void Update() override;


public:

	Ptr<qFlipBook> GetCurFlipBook() { return m_CurFlipBook; }
	Ptr<qSprite> GetCurSprite() { return m_CurSprite; }
	Ptr<qTexture> GetAtlasTex() { return m_AtlasTex; }

	int GetCurSpriteIndex() { return m_CurSpriteIndex; }
	bool* GetCurMode() { return m_Mode; }

	void SetCurSprite(Ptr<qSprite> _Sprite)
	{
		m_CurSprite = _Sprite;
		SetSpriteData();
	}

	Vec2 GetOffset() { return m_Offset; }

	
	bool IsPlaying() { return m_Playing; }
	void SetPlaying(bool _play) { m_Playing = _play; }

private:
	void SetFlipBookData();
	void SetSpriteData();

	void SelectMode();
	void FlipBookInfo();
	void FlipBookPlay();
	void SpriteInfo();
	void SaveFlipBook();


private:
	void SelectFlipBook(DWORD_PTR _AssetName);

private:
	//ListUI*						m_List;

	Ptr<qFlipBook>				m_CurFlipBook;
	Ptr<qSprite>				m_CurSprite;
	Ptr<qTexture>				m_AtlasTex;

	string						m_CurFlipBookName;
	string						m_CurSpriteName;
	float						m_FPS;
	Vec2						m_Offset;
	Vec2						m_Background;
	bool						m_Repeat;
	int							m_CurSpriteIndex;
	int							m_MaxSpriteIndex;

	bool						m_Playing;
	float						m_AccTime;
	float						m_MaxTime;

	bool						m_Mode[2];		// 0 : Create Mode  /  1 : Edit Mode
	bool						m_IsActive;
	path						Path;
};

