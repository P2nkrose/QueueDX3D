#pragma once
#include "qComponent.h"

#include "qFlipBook.h"

class qFlipBookComponent : public qComponent
{
public:
	CLONE(qFlipBookComponent);
	qFlipBookComponent();
	qFlipBookComponent(const qFlipBookComponent& _Origin);
	~qFlipBookComponent();

public:
	virtual void FinalTick() override;


public:
	void Reset();
	void Binding();
	static void Clear();

public:
	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;

public:
	void AddFlipBook(int _Idx, Ptr<qFlipBook> _FlipBook);
	Ptr<qFlipBook> FindFlipBook(const wstring& _Key);
	void Play(int _FliBookIdx, float _FPS, bool _Repeat);

	Ptr<qSprite> GetCurSprite() { return m_CurFrmSprite; }
	void SetCurSprite(Ptr<qSprite> _Sprite) { m_CurFrmSprite = _Sprite; }

	Ptr<qFlipBook> GetCurFlipBook() { return m_CurFlipBook; }
	void SetCurFlipBook(Ptr<qFlipBook> _FlipBook) { m_CurFlipBook = _FlipBook; }


// 추가
public:
	vector<Ptr<qFlipBook>>& GetVecFlipBook() { return m_vecFlipBook; }
	bool IsCurFlipBookFinished() { return m_Finish; }

public:
	int GetMaxFrm() { return m_MaxSpriteIndex; }
	int GetCurFrmIdx() { return m_CurSpriteIndex; }

	bool GetRepeat() { return m_Repeat; }
	void SetRepeat(bool _Repeat);

	float GetFPS() { return m_FPS; }
	void SetFPS(float _fps) { m_FPS = _fps; }

private:
	vector<Ptr<qFlipBook>>			m_vecFlipBook;		// FlipBook 컴포넌트가 보유한 모든 FlipBook 목록
	Ptr<qFlipBook>					m_CurFlipBook;		// 현재 재생중인 FlipBook
	Ptr<qSprite>					m_CurFrmSprite;		// 현재 재생중인 FlipBook 에서 현재 프레임 인덱스에 해당하는 스프라이트
	int								m_CurSpriteIndex;	// 현재 재생중엔 FlipBook 에서 몇번째 Sprite가 재생중인지 인덱스 기록
	int								m_MaxSpriteIndex;	// 현재 재생중인 FlipBook 의 최대 프레임
	float							m_FPS;				// 현재 재생중인 FlipBook 의 초당 프레임 진행 수
	float							m_AccTime;			// 누적 시간값 체크
	bool							m_Repeat;
	bool							m_Finish;			// FlipBook 재생이 끝에 도달했는지 여부

};

