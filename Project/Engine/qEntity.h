#pragma once


class qEntity
{
public:
	qEntity();
	qEntity(const qEntity& _Other);
	virtual ~qEntity();

public:
	// Entity 또한 추상클래스로 설정
	virtual qEntity* Clone() = 0;

	void SetName(const wstring& _Name) { m_Name = _Name; }
	const wstring& GetName() const { return m_Name; }
	UINT GetID() { return m_ID; }


private:
	static UINT		g_ID;

private:
	wstring			m_Name;
	const UINT		m_ID;		// 상수화된 변수는 생성된 이니셜라이저만 넣을수있다.


};

