#pragma once
#include "qAsset.h"

#include "qMesh.h"
#include "qMaterial.h"

class qMeshData : public qAsset
{
public:
	CLONE_DISABLE(qMeshData);
	qMeshData(bool _Engine = false);
	~qMeshData();


public:
	static qMeshData* LoadFromFBX(const wstring& _RelativePath);

	qGameObject* Instantiate();
	virtual int Save(const wstring& _FilePath) override;
	virtual int Load(const wstring& _strFilePath) override;

private:
	Ptr<qMesh>					m_pMesh;
	vector<Ptr<qMaterial>>		m_vecMtrl;
};

