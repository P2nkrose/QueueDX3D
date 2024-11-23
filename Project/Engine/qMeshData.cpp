#include "pch.h"
#include "qMeshData.h"

#include "qPathMgr.h"
#include "qAssetMgr.h"

#include "qGameObject.h"
#include "qTransform.h"
#include "qMeshRender.h"

#include "qFBXLoader.h"

qMeshData::qMeshData(bool _Engine)
    : qAsset(ASSET_TYPE::MESH_DATA)
{
    if (_Engine)
        SetEngineAsset();
}

qMeshData::~qMeshData()
{
}


qGameObject* qMeshData::Instantiate()
{
	qGameObject* pNewObj = new qGameObject;
	pNewObj->AddComponent(new qTransform);
	pNewObj->AddComponent(new qMeshRender);

	pNewObj->MeshRender()->SetMesh(m_pMesh);

	for (UINT i = 0; i < m_vecMtrl.size(); ++i)
	{
		pNewObj->MeshRender()->SetMaterial(m_vecMtrl[i], i);
	}

	return pNewObj;
}

qMeshData* qMeshData::LoadFromFBX(const wstring& _RelativePath)
{
	wstring strFullPath = qPathMgr::GetInst()->GetContentPath();
	strFullPath += _RelativePath;

	qFBXLoader loader;
	loader.init();
	loader.LoadFbx(strFullPath);

	// 메쉬 가져오기
	qMesh* pMesh = nullptr;
	pMesh = qMesh::CreateFromContainer(loader);

	// AssetMgr 에 메쉬 등록
	if (nullptr != pMesh)
	{
		wstring strMeshKey = L"mesh\\";
		strMeshKey += path(strFullPath).stem();
		strMeshKey += L".mesh";
		qAssetMgr::GetInst()->AddAsset<qMesh>(strMeshKey, pMesh);

		// 메시를 실제 파일로 저장
		pMesh->Save(strMeshKey);
	}

	vector<Ptr<qMaterial>> vecMtrl;

	// 메테리얼 가져오기
	for (UINT i = 0; i < loader.GetContainer(0).vecMtrl.size(); ++i)
	{
		// 예외처리 (material 이름이 입력 안되어있을 수도 있다.)
		Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(loader.GetContainer(0).vecMtrl[i].strMtrlName);
		assert(pMtrl.Get());

		vecMtrl.push_back(pMtrl);
	}

	qMeshData* pMeshData = new qMeshData(true);
	pMeshData->m_pMesh = pMesh;
	pMeshData->m_vecMtrl = vecMtrl;

	return pMeshData;
}

int qMeshData::Save(const wstring& _FilePath)
{
    return 0;
}

int qMeshData::Load(const wstring& _strFilePath)
{
    return 0;
}
