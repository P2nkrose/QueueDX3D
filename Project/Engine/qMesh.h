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
	qStructuredBuffer* GetBoneFrameDataBuffer() { return m_pBoneFrameData; } // 전체 본 프레임 정보
	qStructuredBuffer* GetBoneInverseBuffer() { return  m_pBoneInverse; }	   // 각 Bone 의 Inverse 행렬


	virtual int Load(const wstring& _FilePath) override;
	virtual int Save(const wstring& _FilePath) override;


private:
	ComPtr<ID3D11Buffer>    m_VB;
	D3D11_BUFFER_DESC       m_VBDesc;
	UINT                    m_VtxCount;
	Vtx* m_VtxSysMem;

	// 하나의 버텍스버퍼에 여러개의 인덱스버퍼가 연결
	vector<tIndexInfo>		m_vecIdxInfo;

	// Animation3D 정보
	vector<tMTAnimClip>		m_vecAnimClip;
	vector<tMTBone>			m_vecBones;

	qStructuredBuffer*		m_pBoneFrameData;   // 전체 본 프레임 정보(크기, 이동, 회전) (프레임 개수만큼)
	qStructuredBuffer*		m_pBoneInverse;	    // 각 뼈의 offset 행렬(각 뼈의 위치를 되돌리는 행렬) (1행 짜리)
};

