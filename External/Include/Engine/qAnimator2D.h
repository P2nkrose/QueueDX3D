#pragma once
#include "qComponent.h"

class qFlipBook;

class qAnimator2D : public qComponent
{
public:
	CLONE(qAnimator2D);
	qAnimator2D();
	~qAnimator2D();

public:
	virtual void FinalTick() override;


private:
	map<wstring, qFlipBook*>	m_mapAnim;	// Animator2D 컴포넌트가 보유한 모든 FlipBook 목록
	qFlipBook*					m_CurAnim;	// 현재 재생중인 FlipBook
	int							m_CurFrm;	// 현재 재생중엔 FlipBook 에서 몇번째 Sprite가 재생중인지 인덱스 기록
};

