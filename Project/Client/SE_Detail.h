#pragma once
#include "SE_Sub.h"


class SE_Detail : public SE_Sub
{
public:
	SE_Detail();
	~SE_Detail();

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	void SetAtlasTex(Ptr<qTexture> _Tex);
	string GetSpriteName() { return m_SpriteName; }


private:
	void SelectTexture(DWORD_PTR _ListUI);

private:
	void Atlas();
	void AtlasInfo();
	void SpriteInfo();
	void SpriteList();
	void CreateSprite();

private:
	Ptr<qTexture>			m_AtlasTex;
	Ptr<qSprite>			m_CurSprite;
	vector<Ptr<qSprite>>	m_vecAddSprite;

	string					m_SpriteName;

	ImVec2					ImageRectMin;		// Image 위젯 좌상단 실제 위치
	ImVec2					m_MousePos;			// 실제 마우스 위치

	ImVec2					LeftTop;
	ImVec2					RightBottom;

	ImVec2					m_MouseLT;			// 마우스 위치에 해당하는 Texture의 픽셀 좌표 Left Top
	ImVec2					m_MouseRB;			// 마우스 위치에 해당하는 Texture의 픽셀 좌표 Right Bottom
	ImVec2					m_BackGround;

	int						m_CurIndex;

	string					TexName;
	path					Path;

};

