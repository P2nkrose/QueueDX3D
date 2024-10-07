#pragma once
#include "qEntity.h"

class qAsset : public qEntity
{
public:
	friend class qGameObject;

	template<typename T>
	friend class Ptr;

	friend class qAssetMgr;

public:
	qAsset(ASSET_TYPE _Type);
	qAsset(const qAsset& _Other);
	~qAsset();

	// Asset은 모든 Asset의 부모역할을 한다. 즉, 추상클래스이므로 순수가상함수 생성
	virtual qAsset* Clone() { return nullptr; }

public:
	const wstring& GetKey() { return m_Key; }
	const wstring& GetRelativePath() { return m_RelativePath; }
	ASSET_TYPE GetAssetType() { return m_Type; }
	UINT GetRefCount() { return m_RefCount; }
	bool IsEngineAsset() { return m_Engine; }
	void SetRelativePath(const wstring& _path) { m_RelativePath = _path; }

protected:
	void SetKey(const wstring& _Key) { m_Key = _Key; }
	void SetEngineAsset() { m_Engine = true; }

private:
	void AddRef() { ++m_RefCount; }
	void Release()
	{
		--m_RefCount;

		if (m_RefCount <= 0)
			delete this;
	}

	virtual int Save(const wstring& _RelativePath) { return E_FAIL; }
	virtual int Load(const wstring& _FilePath) { return E_FAIL; }


private:
	wstring				m_Key;
	wstring				m_RelativePath;
	const ASSET_TYPE	m_Type;

	int					m_RefCount;

	bool				m_Engine;
};

