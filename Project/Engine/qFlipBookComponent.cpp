#include "pch.h"
#include "qFlipBookComponent.h"

#include "qTimeMgr.h"
#include "qDevice.h"
#include "qConstBuffer.h"
#include "qAssetMgr.h"

#include "qFlipBook.h"

qFlipBookComponent::qFlipBookComponent()
	: qComponent(COMPONENT_TYPE::FLIPBOOKCOMPONENT)
	, m_vecFlipBook{}
	, m_CurFlipBook(nullptr)
	, m_CurFrmSprite(nullptr)
	, m_CurSpriteIndex(0)
	, m_MaxSpriteIndex(0)
	, m_FPS(0.f)
	, m_AccTime(0.f)
	, m_Repeat(false)
	, m_Finish(false)
{
	
}

qFlipBookComponent::qFlipBookComponent(const qFlipBookComponent& _Origin)
	: qComponent(_Origin)
	, m_vecFlipBook(_Origin.m_vecFlipBook)
	, m_CurFlipBook(_Origin.m_CurFlipBook)
	, m_CurSpriteIndex(0)
	, m_MaxSpriteIndex(_Origin.m_MaxSpriteIndex)
	, m_FPS(_Origin.m_FPS)
	, m_AccTime(0.f)
	, m_Repeat(_Origin.m_Repeat)
	, m_Finish(false)
{
	if (nullptr != m_CurFlipBook)
	{
		int FlipBookIdx = 0;
		for (; FlipBookIdx < (int)m_vecFlipBook.size(); ++FlipBookIdx)
		{
			if (m_CurFlipBook == m_vecFlipBook[FlipBookIdx])
				break;
		}

		Play(FlipBookIdx, m_FPS, m_Repeat);
	}
}

qFlipBookComponent::~qFlipBookComponent()
{
}

void qFlipBookComponent::FinalTick()
{
	if (m_Finish)
	{
		if (false == m_Repeat)
			return;

		Reset();
	}

	if (nullptr != m_CurFlipBook)
	{
		float MaxTime = 1.f / m_FPS;

		m_AccTime += DT;

		if (MaxTime < m_AccTime)
		{
			m_AccTime -= MaxTime;
			++m_CurSpriteIndex;

			if (m_CurFlipBook->GetMaxFrameCount() <= m_CurSpriteIndex)
			{
				--m_CurSpriteIndex;
				m_Finish = true;
			}
		}

		m_CurFrmSprite = m_CurFlipBook->GetSprite(m_CurSpriteIndex);
	}
}

void qFlipBookComponent::AddFlipBook(int _Idx, Ptr<qFlipBook> _Flipbook)
{
	if (m_vecFlipBook.size() <= _Idx)
	{
		m_vecFlipBook.resize(_Idx + 1);
	}

	m_vecFlipBook[_Idx] = _Flipbook;
}

Ptr<qFlipBook> qFlipBookComponent::FindFlipBook(const wstring& _Key)
{
	for (size_t i = 0; i < m_vecFlipBook.size(); ++i)
	{
		if (m_vecFlipBook[i]->GetKey() == _Key)
			return m_vecFlipBook[i];
	}

	return nullptr;
}


void qFlipBookComponent::Play(int _FliBookIdx, float _FPS, bool _Repeat)
{
	m_CurFlipBook = m_vecFlipBook[_FliBookIdx];

	if (nullptr == m_CurFlipBook)
	{
		return;
	}

	m_CurSpriteIndex = 0;
	m_AccTime = 0.f;
	m_FPS = _FPS;
	m_Repeat = _Repeat;
}


void qFlipBookComponent::Reset()
{
	m_CurSpriteIndex = 0;
	m_AccTime = 0.f;
	m_Finish = false;
}

void qFlipBookComponent::Binding()
{
	if (nullptr != m_CurFrmSprite)
	{
		// 현재 표시해야하는 Sprite 의 정보를 Sprite 전용 상수버퍼를 통해서 GPU 에 전달
		tSpriteInfo tInfo = {};

		tInfo.LeftTopUV = m_CurFrmSprite->GetLeftTopUV();
		tInfo.SliceUV = m_CurFrmSprite->GetSliceUV();
		tInfo.BackGroundUV = m_CurFrmSprite->GetBackgroundUV();
		tInfo.OffsetUV = m_CurFrmSprite->GetOffsetUV();
		tInfo.UseFlipbook = 1;

		static qConstBuffer* CB = qDevice::GetInst()->GetConstBuffer(CB_TYPE::SPRITE);

		CB->SetData(&tInfo);
		CB->Binding();

		// FlipBook Sprite 아틀라스 텍스쳐 전용 레지스터번호 t10 에 바인딩		
		Ptr<qTexture> pAtlas = m_CurFrmSprite->GetAtlasTexture();
		pAtlas->Binding(10);
	}
	else
	{
		Clear();
	}
}

void qFlipBookComponent::Clear()
{
	tSpriteInfo tInfo = {};
	static qConstBuffer* CB = qDevice::GetInst()->GetConstBuffer(CB_TYPE::SPRITE);
	CB->SetData(&tInfo);
	CB->Binding();
}



//int qFlipBookComponent::GetCurFrmIdx()
//{
//	if (m_CurFlipBook == nullptr)
//		return -1;
//
//	for (int i = 0; i < m_vecFlipBook.size(); ++i)
//	{
//		if (m_vecFlipBook[i] == m_CurFlipBook)
//			return i;
//	}
//
//	return -1;
//}


void qFlipBookComponent::SetRepeat(bool _Repeat)
{
	m_Repeat = _Repeat;
}


void qFlipBookComponent::SaveToFile(FILE* _File)
{
	// FlipBook 에셋 목록 저장
	size_t FlipBookCount = m_vecFlipBook.size();
	fwrite(&FlipBookCount, sizeof(size_t), 1, _File);
	for (size_t i = 0; i < m_vecFlipBook.size(); ++i)
	{
		SaveAssetRef(m_vecFlipBook[i], _File);
	}

	// 현재 재생중인 FlipBook 정보 저장
	SaveAssetRef(m_CurFlipBook, _File);

	// 현재 재생중인 FlipBook 내에서 지정된 Sprite
	SaveAssetRef(m_CurFrmSprite, _File);

	// 현재 재생중인 FlipBook 내에서 지정된 Sprite 가 몇 번째 인덱스인지
	fwrite(&m_CurSpriteIndex, sizeof(int), 1, _File);
	fwrite(&m_FPS, sizeof(float), 1, _File);
	fwrite(&m_AccTime, sizeof(float), 1, _File);
	fwrite(&m_Repeat, sizeof(bool), 1, _File);

}

void qFlipBookComponent::LoadFromFile(FILE* _File)
{
	// FlipBook 에셋 목록 불러오기
	size_t FlipBookCount = 0;
	fread(&FlipBookCount, sizeof(size_t), 1, _File);
	for (size_t i = 0; i < FlipBookCount; ++i)
	{
		Ptr<qFlipBook> pFlipBook;
		LoadAssetRef(pFlipBook, _File);
		m_vecFlipBook.push_back(pFlipBook);
	}

	// 현재 재생중인 FlipBook 정보 로드
	LoadAssetRef(m_CurFlipBook, _File);

	// 현재 재생중인 FlipBook 내에서 지정된 Sprite
	LoadAssetRef(m_CurFrmSprite, _File);

	// 현재 재생중인 FlipBook 내에서 지정된 Sprite 가 몇번째 인덱스인지
	fread(&m_CurSpriteIndex, sizeof(int), 1, _File);
	fread(&m_FPS, sizeof(float), 1, _File);
	fread(&m_AccTime, sizeof(float), 1, _File);
	fread(&m_Repeat, sizeof(bool), 1, _File);

}
