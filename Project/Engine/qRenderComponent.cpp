#include "pch.h"
#include "qRenderComponent.h"

#include "qAssetMgr.h"
#include "qLevelMgr.h"
#include "qLevel.h"

#include "qTransform.h"

qRenderComponent::qRenderComponent(COMPONENT_TYPE _Type)
	: qComponent(_Type)
	, m_Mesh(nullptr)
	, m_Mtrl(nullptr)
	, m_FrustumCheck(true)
{
}

qRenderComponent::qRenderComponent(const qRenderComponent& _Origin)
	: qComponent(_Origin)
	, m_Mesh(_Origin.m_Mesh)
	, m_Mtrl(_Origin.m_Mtrl)
	, m_SharedMtrl(_Origin.m_Mtrl)
	, m_FrustumCheck(_Origin.m_FrustumCheck)
{
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	if (nullptr != pCurLevel)
	{
		assert(!(pCurLevel->GetState() != LEVEL_STATE::PLAY
			&& nullptr != _Origin.m_DynamicMtrl));
	}

	if (nullptr != _Origin.m_DynamicMtrl)
	{
		GetDynamicMaterial();
	}
}

qRenderComponent::~qRenderComponent()
{
}

void qRenderComponent::render_shadowmap()
{
	// 재질은 ShadowMapMtrl 로 이미 Binding 되어 있는 걸 사용할 것
	// 자신이 선택한 Mesh 로 렌더링 요청을 하면 된다.
	Transform()->Binding();
	GetMesh()->Render();
}

void qRenderComponent::SetMaterial(Ptr<qMaterial> _Mtrl)
{
	m_Mtrl = m_SharedMtrl = _Mtrl;
}

Ptr<qMaterial> qRenderComponent::GetSharedMtrl()
{
	m_Mtrl = m_SharedMtrl;
	return m_Mtrl;
}

Ptr<qMaterial> qRenderComponent::GetDynamicMaterial()
{
	// 동적 재질 생성 및 반환은 게임(레벨) 이 Play 모드인 경우에만 호출이 되어야 한다.
	assert(qLevelMgr::GetInst()->GetCurrentLevel()->GetState() == LEVEL_STATE::PLAY);

	if (nullptr != m_DynamicMtrl)
		return m_Mtrl = m_DynamicMtrl;

	m_Mtrl = m_DynamicMtrl = m_SharedMtrl->Clone();

	return m_Mtrl;
}

void qRenderComponent::SaveDataToFile(FILE* _File)
{
	SaveAssetRef(m_Mesh, _File);
	SaveAssetRef(m_Mtrl, _File);
	SaveAssetRef(m_SharedMtrl, _File);
}

void qRenderComponent::LoadDataFromFile(FILE* _File)
{
	LoadAssetRef(m_Mesh, _File);
	LoadAssetRef(m_Mtrl, _File);
	LoadAssetRef(m_SharedMtrl, _File);
}
