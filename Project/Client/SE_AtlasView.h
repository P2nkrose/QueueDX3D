#pragma once
#include "SE_Sub.h"


class SE_AtlasView : public SE_Sub
{
public:
	friend class SE_Detail;
	SE_AtlasView();
	~SE_AtlasView();

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	void SetAtlasTex(Ptr<qTexture> _Tex);

public:
	ImVec2 GetLeftTop() { return m_MouseLT; }
	ImVec2 GetRightBottom() { return m_MouseRB; }


private:
	void WheelCheck();
	void SelectCheck();
	void DrawSelectRect();
	void CalcSpriteSize(Vec2 _PixelPos);
	bool IsPixelOk(Vec2 _PixelPos);


private:
	Ptr<qTexture>		m_AtlasTex;

	ImVec2				ImageRectMin;		// Image 위젯 좌상단 실제 위치
	ImVec2				m_MousePos;			// 실제 마우스 위치

	ImVec2				m_MouseLT;			// 마우스 위치에 해당하는 Texture의 픽셀 좌표 Left Top
	ImVec2				m_MouseRB;			// 마우스 위치에 해당하는 Texture의 픽셀 좌표 Right Bottom

	set<Vec2>			m_PixelID;			// 등록된 적이 있는 픽셀인지 확인하는 용도

	float				m_WidthSize;
	float				m_WheelScale;
	float				m_Ratio;			// 실제 해상도 대비 출력 이미지의 비율


};

