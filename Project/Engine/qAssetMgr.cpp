#include "pch.h"
#include "qAssetMgr.h"

#include "assets.h"

qAssetMgr::qAssetMgr()
{
}

qAssetMgr::~qAssetMgr()
{
	//if (nullptr != m_FMODSystem)
	//{
	//	m_FMODSystem->release();
	//	m_FMODSystem = nullptr;
	//}
}


void qAssetMgr::Tick()
{
	if (m_Changed)
		m_Changed = false;

}


Ptr<qAsset> qAssetMgr::FindAsset(ASSET_TYPE _Type, const wstring& _Key)
{
	map<wstring, Ptr<qAsset>>::iterator iter = m_mapAsset[(UINT)_Type].find(_Key);

	if (iter == m_mapAsset[(UINT)_Type].end())
	{
		return nullptr;
	}

	return iter->second;
}

Ptr<qTexture> qAssetMgr::CreateTexture(wstring _strKey, UINT _Width, UINT _Height
									 , DXGI_FORMAT _Format, UINT _Flags, D3D11_USAGE _Usage)
{
	// 중복 키 검사
	Ptr<qTexture> pTexture = FindAsset<qTexture>(_strKey);
	assert(!pTexture.Get());

	pTexture = new qTexture;
	if (FAILED(pTexture->Create(_Width, _Height, _Format, _Flags, _Usage)))
	{
		MessageBox(nullptr, L"텍스쳐 생성 실패", L"텍스쳐 생성 실패", MB_OK);
		return nullptr;
	}

	pTexture->m_Key = _strKey;
	pTexture->SetEngineAsset();
	m_mapAsset[(UINT)ASSET_TYPE::TEXTURE].insert(make_pair(_strKey, pTexture.Get()));

	return pTexture;
	
}

Ptr<qTexture> qAssetMgr::CreateTexture(wstring _strKey, ComPtr<ID3D11Texture2D> _Tex2D)
{
	// 중복키 검사
	Ptr<qTexture> pTexture = FindAsset<qTexture>(_strKey);
	assert(!pTexture.Get());

	pTexture = new qTexture;
	if (FAILED(pTexture->Create(_Tex2D)))
	{
		MessageBox(nullptr, L"텍스쳐 생성 실패", L"텍스쳐 생성 실패", MB_OK);
		return nullptr;
	}

	pTexture->m_Key = _strKey;
	pTexture->SetEngineAsset();
	m_mapAsset[(UINT)ASSET_TYPE::TEXTURE].insert(make_pair(_strKey, pTexture.Get()));

	return pTexture;
}

void qAssetMgr::GetAssetNames(ASSET_TYPE _Type, vector<string>& _vecOut)
{
	for (const auto& pair : m_mapAsset[(UINT)_Type])
	{
		_vecOut.push_back(string(pair.first.begin(), pair.first.end()));
	}
}


void qAssetMgr::DeleteAsset(ASSET_TYPE _Type, const wstring& _Key)
{
	map<wstring, Ptr<qAsset>>::iterator iter = m_mapAsset[(UINT)_Type].find(_Key);
	assert(iter != m_mapAsset[(UINT)_Type].end());
	m_mapAsset[(UINT)_Type].erase(iter);

	// Asset 변경 알림
	qTaskMgr::GetInst()->AddTask(tTask{ ASSET_CHANGED });
}