#pragma once
#include "qComponent.h"

class qStructuredBuffer;

class qAnimator3D : public qComponent
{
public:
	CLONE(qAnimator3D);
	qAnimator3D();
	qAnimator3D(const qAnimator3D& _origin);
	~qAnimator3D();

public:
	virtual void FinalTick() override;
	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;

public:
    void SetBones(const vector<tMTBone>* _vecBones) { m_pVecBones = _vecBones; m_vecFinalBoneMat.resize(m_pVecBones->size()); }
    void SetAnimClip(const vector<tMTAnimClip>* _vecAnimClip);
    void SetClipTime(int _iClipIdx, float _fTime) { m_vecClipUpdateTime[_iClipIdx] = _fTime; }

    qStructuredBuffer* GetFinalBoneMat() { return m_pBoneFinalMatBuffer; }
    UINT GetBoneCount() { return (UINT)m_pVecBones->size(); }
    void ClearData();

    void Binding();


private:
    void check_mesh(Ptr<qMesh> _pMesh);


private:
    const vector<tMTBone>*      m_pVecBones;
    const vector<tMTAnimClip>*  m_pVecClip;

    vector<float>				m_vecClipUpdateTime;
    vector<Matrix>				m_vecFinalBoneMat;      // 텍스쳐에 전달할 최종 행렬정보
    int							m_iFrameCount;          // 30
    double						m_dCurTime;
    int							m_iCurClip;             // 클립 인덱스	

    int							m_iFrameIdx;            // 클립의 현재 프레임
    int							m_iNextFrameIdx;        // 클립의 다음 프레임
    float						m_fRatio;	            // 프레임 사이 비율

    qStructuredBuffer*          m_pBoneFinalMatBuffer;  // 특정 프레임의 최종 행렬
    bool						m_bFinalMatUpdate;      // 최종행렬 연산 수행여부
};

