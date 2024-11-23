#pragma once
#include "qComponent.h"

struct tMtrlSet
{
	Ptr<qMaterial> pSharedMtrl;		// 공유 머테리얼
	Ptr<qMaterial> pDynamicMtrl;	// 공유 머테리얼의 복사본
	Ptr<qMaterial> pCurMtrl;		// 현재 사용할 머테리얼
};

class qRenderComponent : public qComponent
{
public:
	qRenderComponent(COMPONENT_TYPE _Type);
	qRenderComponent(const qRenderComponent& _Origin);
	~qRenderComponent();

public:
	virtual qRenderComponent* Clone() PURE;
	virtual void FinalTick() PURE;
	virtual void Render() PURE;
	
	virtual void render_shadowmap();

public:
	void SetMesh(Ptr<qMesh> _Mesh);
	Ptr<qMesh> GetMesh() { return m_Mesh; }
	
	void SetMaterial(Ptr<qMaterial> _Mtrl, UINT _idx);
	Ptr<qMaterial> GetMaterial(UINT _idx);
	Ptr<qMaterial> GetSharedMaterial(UINT _idx);


	// 동적 재질 생성 및 반환
	Ptr<qMaterial> GetDynamicMaterial(UINT _idx);

	UINT GetMaterialCount() { return (UINT)m_vecMtrls.size(); }

public:
	void SetFrustumCheck(bool _Check) { m_FrustumCheck = _Check; }
	bool IsFrustumCheck() { return m_FrustumCheck; }


protected:
	void SaveDataToFile(FILE* _File);
	void LoadDataFromFile(FILE* _File);


private:
	Ptr<qMesh>					m_Mesh;

	vector<tMtrlSet>			m_vecMtrls;		// 재질

	bool						m_FrustumCheck; // 절두체 체크를 받을것인지 말것인지
};

	