#pragma once
#include "qComponent.h"

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
	void SetMesh(Ptr<qMesh> _Mesh) { m_Mesh = _Mesh; }
	void SetMaterial(Ptr<qMaterial> _Mtrl);

	Ptr<qMesh> GetMesh() { return m_Mesh; }
	Ptr<qMaterial> GetMaterial() { return m_Mtrl; }
	Ptr<qMaterial> GetSharedMtrl();


	// 동적 재질 생성 및 반환
	Ptr<qMaterial> GetDynamicMaterial();

public:
	void SetFrustumCheck(bool _Check) { m_FrustumCheck = _Check; }
	bool IsFrustumCheck() { return m_FrustumCheck; }


protected:
	void SaveDataToFile(FILE* _File);
	void LoadDataFromFile(FILE* _File);


private:
	Ptr<qMesh>					m_Mesh;

	Ptr<qMaterial>				m_Mtrl;			// 현재 사용중인 재질
	Ptr<qMaterial>				m_SharedMtrl;	// 공유 재질 (마스터)
	Ptr<qMaterial>				m_DynamicMtrl;	// 임시(동적) 재질

	bool						m_FrustumCheck; // 절두체 체크를 받을것인지 말것인지
};

	