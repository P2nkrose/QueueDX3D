#pragma once
#include "qAsset.h"

#include "qFBXLoader.h"

class qStructuredBuffer;

struct tIndexInfo
{
	ComPtr<ID3D11Buffer>    pIB;
	D3D11_BUFFER_DESC       tIBDesc;
	UINT				    iIdxCount;
	void*					pIdxSysMem;
};


class qMesh : public qAsset
{
public:
	qMesh(bool _IsEngine = false);
	~qMesh();

public:
	static qMesh* CreateFromContainer(qFBXLoader& _loader);
	int Create(Vtx* _VtxSysMem, UINT _VtxCount, UINT* _IdxSysMem, UINT _IdxCount);

	void Binding(UINT _Subset);
	void Render(UINT _Subset);
	void Render_Particle(UINT _Count);

	UINT GetVertexCount() { return m_VtxCount; }
	UINT GetSubsetCount() { return (UINT)m_vecIdxInfo.size(); }

	void* GetVtxSysMem() { return m_VtxSysMem; }

	const vector<tMTBone>* GetBones() { return &m_vecBones; }
	UINT GetBoneCount() { return (UINT)m_vecBones.size(); }
	const vector<tMTAnimClip>* GetAnimClip() { return &m_vecAnimClip; }
	bool IsAnimMesh() { return !m_vecAnimClip.empty(); }
	qStructuredBuffer* GetBoneFrameDataBuffer() { return m_pBoneFrameData; } // ��ü �� ������ ����
	qStructuredBuffer* GetBoneInverseBuffer() { return  m_pBoneInverse; }	   // �� Bone �� Inverse ���


	virtual int Load(const wstring& _FilePath) override;
	virtual int Save(const wstring& _FilePath) override;


private:
	ComPtr<ID3D11Buffer>    m_VB;
	D3D11_BUFFER_DESC       m_VBDesc;
	UINT                    m_VtxCount;
	Vtx* m_VtxSysMem;

	// �ϳ��� ���ؽ����ۿ� �������� �ε������۰� ����
	vector<tIndexInfo>		m_vecIdxInfo;

	// Animation3D ����
	vector<tMTAnimClip>		m_vecAnimClip;
	vector<tMTBone>			m_vecBones;

	qStructuredBuffer*		m_pBoneFrameData;   // ��ü �� ������ ����(ũ��, �̵�, ȸ��) (������ ������ŭ)
	qStructuredBuffer*		m_pBoneInverse;	    // �� ���� offset ���(�� ���� ��ġ�� �ǵ����� ���) (1�� ¥��)
};

