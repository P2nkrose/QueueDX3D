#include "pch.h"
#include "qPrefab.h"

#include "qGameObject.h"

OBJECT_SAVE  qPrefab::g_ObjectSaveFunc = nullptr;
OBJECT_LOAD  qPrefab::g_ObjectLoadFunc = nullptr;

qPrefab::qPrefab()
	: qAsset(ASSET_TYPE::PREFAB)
	, m_ProtoObject(nullptr)
{
}

qPrefab::~qPrefab()
{
	if (nullptr != m_ProtoObject)
		delete m_ProtoObject;
}

qGameObject* qPrefab::Instantiate()
{
	return m_ProtoObject->Clone();
}


int qPrefab::Save(const wstring& _FilePath)
{
	FILE* File = nullptr;
	_wfopen_s(&File, _FilePath.c_str(), L"wb");

	if (nullptr == File)
		return E_FAIL;

	g_ObjectSaveFunc(File, m_ProtoObject);

	fclose(File);

	return S_OK;
}


int qPrefab::Load(const wstring& _FilePath)
{
	FILE* File = nullptr;
	_wfopen_s(&File, _FilePath.c_str(), L"rb");

	if (nullptr == File)
		return E_FAIL;

	m_ProtoObject = g_ObjectLoadFunc(File);

	fclose(File);

	return S_OK;
}


