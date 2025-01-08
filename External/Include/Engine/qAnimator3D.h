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
    vector<Matrix>				m_vecFinalBoneMat;      // �ؽ��Ŀ� ������ ���� �������
    int							m_iFrameCount;          // 30
    double						m_dCurTime;
    int							m_iCurClip;             // Ŭ�� �ε���	

    int							m_iFrameIdx;            // Ŭ���� ���� ������
    int							m_iNextFrameIdx;        // Ŭ���� ���� ������
    float						m_fRatio;	            // ������ ���� ����

    qStructuredBuffer*          m_pBoneFinalMatBuffer;  // Ư�� �������� ���� ���
    bool						m_bFinalMatUpdate;      // ������� ���� ���࿩��
};

