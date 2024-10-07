#include "pch.h"
#include "AE_Preview.h"
#include "AE_Detail.h"
#include "AE_SpriteList.h"

#include <Engine/qSprite.h>
#include <Engine/qTexture.h>
#include <Engine/qFlipBook.h>
#include <Engine/qFlipBookComponent.h>
#include <Engine/qTimeMgr.h>


AE_Preview::AE_Preview()
	: m_ViewerSize(ImVec2(200.f, 200.f))
	, m_CurSpriteIndex(0)
	, m_Playing(false)
	, m_CurFlipBook(nullptr)
{

}

AE_Preview::~AE_Preview()
{
	
}

void AE_Preview::Init()
{
	if (m_CurSprite != nullptr)
	{
		m_Offset = GetDetail()->GetOffset();
	}
}


void AE_Preview::Update()
{
	if (m_CurSprite == nullptr)
	{
	}
	else
	{
		m_Playing = GetDetail()->IsPlaying();
	}
	  
	SetImage();
}



void AE_Preview::SetImage()
{
	m_CurFlipBook = GetDetail()->GetCurFlipBook();

	//if (nullptr != m_CurFlipBook)
	//{
	//	m_CurSpriteIndex = GetDetail()->GetCurSpriteIndex();
	//	m_CurSprite = m_CurFlipBook->GetSprite(m_CurSpriteIndex);
	//}

	if (nullptr != m_CurFlipBook)
	{
		m_CurSpriteIndex = GetDetail()->GetCurSpriteIndex();

		// FlipBook에 스프라이트가 있는지 먼저 확인
		if (m_CurSpriteIndex >= 0 && m_CurSpriteIndex < m_CurFlipBook->GetMaxFrameCount())
		{
			// 스프라이트가 있는 경우에만 이미지 설정
			m_CurSprite = m_CurFlipBook->GetSprite(m_CurSpriteIndex);
		}
		else
		{
			// 스프라이트가 없는 경우, 기본 이미지나 null로 초기화
			m_CurSprite = nullptr;
		}
	}
	else
	{
		// FlipBook이 없는 경우 기본값 설정
		m_CurSprite = nullptr;
	}



	// Viewer Frame
	if (m_CurSprite != nullptr)
	{
		m_AtlasTex = m_CurSprite->GetAtlasTexture();


		ImVec2 crop = ImVec2(m_CurSprite->GetBackgroundUV().x * m_AtlasTex->Width()
						   , m_CurSprite->GetBackgroundUV().y * m_AtlasTex->Height());

		if (m_ViewerSize.x != crop.x || m_ViewerSize.y != crop.y)
		{
			float ratio = crop.x / m_ViewerSize.x;
			ratio = 1 / ratio;

			crop.x *= ratio;
			crop.y *= ratio;
		}

		float fWidth = m_AtlasTex.Get()->Width();
		float fHeight = m_AtlasTex.Get()->Height();
		Vec2 fFrameOffset;
		fFrameOffset = m_Offset / Vec2(fWidth, fHeight);

		ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ImVec4 border_col = ImVec4(0.7f, 0.7f, 0.7f, 0.7f);

		Vec2 StartUV = Vec2(m_CurSprite->GetLeftTopUV().x, m_CurSprite->GetLeftTopUV().y);
		Vec2 EndUV = Vec2(m_CurSprite->GetLeftTopUV().x + m_CurSprite->GetSliceUV().x
							, m_CurSprite->GetLeftTopUV().y + m_CurSprite->GetSliceUV().y);

		ImGui::SetCursorPosX((ImGui::GetWindowSize().x * 0.5f) - 100.f);
		ImGui::SetCursorPosY((ImGui::GetWindowSize().y * 0.5f) - 100.f);
		ImGui::Image(m_AtlasTex->GetSRV().Get()
			, crop, ImVec2(StartUV.x - fFrameOffset.x, StartUV.y - fFrameOffset.y)
			, ImVec2(EndUV.x - fFrameOffset.x, EndUV.y - fFrameOffset.y), tint_col, border_col);
	}
}



