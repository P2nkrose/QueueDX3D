#pragma once
#include "AE_Sub.h"

class AE_Preview : public AE_Sub
{
public:
	friend class AE_Detail;
	friend class AE_SpriteList;

	AE_Preview();
	~AE_Preview();

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	void SetCurSprite(Ptr<qSprite> _Sprite) { m_CurSprite = _Sprite; }


private:

	void SetImage();


private:
	Ptr<qFlipBook>				m_CurFlipBook;
	Ptr<qSprite>				m_CurSprite;
	Ptr<qTexture>				m_AtlasTex;

	ImVec2						m_ImageRectMin;
	ImVec2						m_ViewerSize;

	Vec2						m_Offset;

	int							m_CurSpriteIndex;

	bool						m_Playing;


	//int						m_MaxSpriteIndex;
	//bool						m_Repeat;
	//bool						m_Finish;




};

