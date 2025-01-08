#include "pch.h"
#include "qMeshData.h"

#include "qPathMgr.h"
#include "qAssetMgr.h"

#include "qGameObject.h"
#include "qTransform.h"
#include "qMeshRender.h"
#include "qAnimator3D.h"

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


	// Animation ��Ʈ �߰�
	if (false == m_pMesh->IsAnimMesh())
		return pNewObj;

	qAnimator3D* pAnimator = new qAnimator3D;
	pNewObj->AddComponent(pAnimator);

	pAnimator->SetBones(m_pMesh->GetBones());
	pAnimator->SetAnimClip(m_pMesh->GetAnimClip());

	return pNewObj;
}

qMeshData* qMeshData::LoadFromFBX(const wstring& _RelativePath)
{
	wstring strFullPath = qPathMgr::GetInst()->GetContentPath();
	strFullPath += _RelativePath;

	qFBXLoader loader;
	loader.init();
	loader.LoadFbx(strFullPath);

	// �޽� ��������
	qMesh* pMesh = nullptr;
	pMesh = qMesh::CreateFromContainer(loader);

	// AssetMgr �� �޽� ���
	if (nullptr != pMesh)
	{
		wstring strMeshKey = L"mesh\\";
		strMeshKey += path(strFullPath).stem();
		strMeshKey += L".mesh";
		
		if (!qAssetMgr::GetInst()->FindAsset<qMesh>(strMeshKey))
		{
			// �޽ø� ���� ���Ϸ� ����
			qAssetMgr::GetInst()->AddAsset<qMesh>(strMeshKey, pMesh);
			pMesh->Save(qPathMgr::GetInst()->GetContentPath() + strMeshKey);
		}

	}

	vector<Ptr<qMaterial>> vecMtrl;

	// ���׸��� ��������
	for (UINT i = 0; i < loader.GetContainer(0).vecMtrl.size(); ++i)
	{
		// ����ó�� (material �̸��� �Է� �ȵǾ����� ���� �ִ�.)
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
	wstring strRelativePath = qPathMgr::GetInst()->GetRelativePath(_FilePath);
	SetRelativePath(strRelativePath);

	wstring strFilePath = qPathMgr::GetInst()->GetContentPath() + strRelativePath;

	FILE* pFile = nullptr;
	errno_t err = _wfopen_s(&pFile, strFilePath.c_str(), L"wb");
	assert(pFile);

	// Mesh Key ����	
	// Mesh Data ����
	SaveAssetRef(m_pMesh, pFile);

	// material ���� ����
	UINT iMtrlCount = (UINT)m_vecMtrl.size();
	fwrite(&iMtrlCount, sizeof(UINT), 1, pFile);

	UINT i = 0;
	wstring strMtrlPath = qPathMgr::GetInst()->GetContentPath();
	strMtrlPath += L"material\\";

	for (; i < iMtrlCount; ++i)
	{
		if (nullptr == m_vecMtrl[i])
			continue;

		// Material �ε���, Key, Path ����
		fwrite(&i, sizeof(UINT), 1, pFile);
		SaveAssetRef(m_vecMtrl[i], pFile);
	}

	i = -1; // ���� ��
	fwrite(&i, sizeof(UINT), 1, pFile);

	fclose(pFile);

	return S_OK;
}

int qMeshData::Load(const wstring& _FilePath)
{
	FILE* pFile = NULL;
	_wfopen_s(&pFile, _FilePath.c_str(), L"rb");

	assert(pFile);

	// Mesh Load
	LoadAssetRef(m_pMesh, pFile);
	assert(m_pMesh.Get());

	// material ���� �б�
	UINT iMtrlCount = 0;
	fread(&iMtrlCount, sizeof(UINT), 1, pFile);

	m_vecMtrl.resize(iMtrlCount);

	for (UINT i = 0; i < iMtrlCount; ++i)
	{
		UINT idx = -1;
		fread(&idx, 4, 1, pFile);
		if (idx == -1)
			break;

		wstring strKey, strPath;

		Ptr<qMaterial> pMtrl;
		LoadAssetRef(pMtrl, pFile);

		m_vecMtrl[i] = pMtrl;
	}

	fclose(pFile);

	return S_OK;
}
