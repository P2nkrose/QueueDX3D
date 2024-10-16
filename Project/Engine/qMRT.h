#pragma once
#include "qEntity.h"

#include "Ptr.h"
#include "qTexture.h"

class qMRT : public qEntity
{
public:
	CLONE_DISABLE(qMRT);
	qMRT();
	~qMRT();

public:
	Ptr<qTexture> GetRT(int _Index) { return m_arrRT[_Index]; }

	void Create(int _RTCount, Ptr<qTexture>* _arrRT, Ptr<qTexture> _DSTex);
	void SetClearColor(Vec4* _Color, bool _Independent);
	void OMSet();

	void Clear() { ClearRT(); ClearDS(); }
	void ClearRT();
	void ClearDS();



private:
	Ptr<qTexture>		m_arrRT[8];			// 최대 설정 가능한 Render Target 개수가 8개
	Vec4				m_ClearColor[8];
	int					m_RTCount;

	Ptr<qTexture>		m_DSTex;			// 깊이 텍스쳐. 없어도 가능하다.

	D3D11_VIEWPORT		m_ViewPort;			// MRT 뷰포트 설정 값
};

