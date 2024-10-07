#pragma once
#include "qAsset.h"

class qSprite : public qAsset
{
public:
	qSprite();
	~qSprite();


public:
	void Create(Ptr<qTexture> _Atlas, Vec2 _LeftTopPixel, Vec2 _SlicePixel);

	virtual int Load(const wstring& _FilePath) override;
	virtual int Save(const wstring& _FilePath) override;
	
public:
	Ptr<qTexture> GetAtlasTexture() { return m_Atlas; }		// 이 Sprite 조각이 어느 아틀라스에서 나온 조각인지
	Ptr<qTexture> GetSprite() { return m_Sprite; }

	void SetLeftTop(Vec2 _LeftTop);			
	void SetSlice(Vec2 _Slice);				
	void SetBackground(Vec2 _Background);
	void SetOffset(Vec2 _Offset);

	Vec2 GetLeftTopUV() { return m_LeftTopUV; }				// 좌상단 UV 지점
	Vec2 GetSliceUV() { return m_SliceUV; }					// 자를 UV 사이즈
	Vec2 GetBackgroundUV() { return m_BackgroundUV; }
	Vec2 GetOffsetUV() { return m_OffsetUV; }



private:
	Ptr<qTexture>		m_Atlas;
	Ptr<qTexture>		m_Sprite;

	Vec2				m_LeftTopUV;	// UV 좌표계
	Vec2				m_SliceUV;		// UV 좌표계
	Vec2				m_BackgroundUV;
	Vec2				m_OffsetUV;
};

