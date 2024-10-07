#pragma once
#include "AE_Sub.h"

class AE_SpriteList : public AE_Sub
{
public:
	friend class AE_Detail;
	friend class AE_Preview;

	AE_SpriteList();
	~AE_SpriteList();

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	void SetSpriteToList(vector<Ptr<qSprite>>& _vecSprite);

	void SetCurSpriteIndex(int _index) { m_ListIndex = _index; }
	int GetCurSpriteIndex() { return m_ListIndex; }

	int GetSpriteCount() { return m_vecAddedSprite.size(); }
	Ptr<qSprite> GetCurSprite() { return m_vecAddedSprite[m_ListIndex]; }


private:
	void ShowList();
	void SelectSprite(DWORD_PTR _AssetName);

private:
	vector<Ptr<qSprite>>		m_vecAddedSprite;

	int							m_ListIndex;
	bool						m_IsActive;

};

