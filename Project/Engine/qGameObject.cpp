#include "pch.h"
#include "qGameObject.h"

#include "qTimeMgr.h"
#include "qKeyMgr.h"

#include "qLevelMgr.h"
#include "qLevel.h"
#include "qLayer.h"

#include "components.h"
#include "qScript.h"

qGameObject::qGameObject()
	: m_arrCom{}
	, m_RenderCom(nullptr)
	, m_Parent(nullptr)
	, m_LayerIdx(-1)	// -1 : 어느 레이어 소속도 아니다 (레벨 안에 있지 않은 상태)
	, m_Dead(false)
{
}

qGameObject::qGameObject(const qGameObject& _Origin)
	: qEntity(_Origin)
	, m_arrCom{}
	, m_RenderCom(nullptr)
	, m_Parent(nullptr)
	, m_LayerIdx(-1)
	, m_Dead(false)
{
	// 컴포넌트 복사
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == _Origin.m_arrCom[i])
			continue;

		qComponent* pClonedCom = _Origin.m_arrCom[i]->Clone();

		AddComponent(pClonedCom);

		pClonedCom->Init();
	}

	// Script 복사
	for (size_t i = 0; i < _Origin.m_vecScript.size(); ++i)
	{
		AddComponent(_Origin.m_vecScript[i]->Clone());
	}

	// 자식 오브젝트 복사
	for (size_t i = 0; i < _Origin.m_vecChildren.size(); ++i)
	{
		AddChild(_Origin.m_vecChildren[i]->Clone());
	}
}

qGameObject::~qGameObject()
{
	Delete_Array(m_arrCom);
	Delete_Vec(m_vecScript);
	Delete_Vec(m_vecChildren);
}


void qGameObject::AddComponent(qComponent* _Component)
{
	COMPONENT_TYPE Type = _Component->GetComponentType();

	if (COMPONENT_TYPE::SCRIPT == Type)
	{
		m_vecScript.push_back((qScript*)_Component);
		_Component->SetOwner(this);
	}
	else
	{
		assert(nullptr == m_arrCom[(UINT)Type]);

		m_arrCom[(UINT)Type] = _Component;
		m_arrCom[(UINT)Type]->SetOwner(this);

		qRenderComponent* pRenderCom = dynamic_cast<qRenderComponent*>(_Component);

		assert(!(pRenderCom && m_RenderCom));

		if (pRenderCom)
			m_RenderCom = pRenderCom;
	}
}

qGameObject* qGameObject::GetChild(const wstring& _ChildName)
{
	for (int i = 0; i < m_vecChildren.size(); ++i)
	{
		if (m_vecChildren[i]->GetName() == _ChildName)
			return m_vecChildren[i];
	}

	return nullptr;
}

void qGameObject::AddChild(qGameObject* _ChildObject)
{
	// 부모 오브젝트는 Level 에 속해있고, AddChild 되는 자식 오브젝트는 레벨에 소속되지 않은 경우
	if (-1 != m_LayerIdx && -1 == _ChildObject->m_LayerIdx)
	{
		assert(nullptr);
	}

	// 자식으로 들어오는 오브젝트가 이미 부모가 있는 경우
	if (_ChildObject->GetParent())
	{
		_ChildObject->DeregisterChild();
	}

	// 자식으로 들어오는 오브젝트가 최상위 부모 오브젝트인 경우
	else
	{
		if (-1 != _ChildObject->m_LayerIdx)
		{
			qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
			if (nullptr != pCurLevel)
			{
				qLayer* pLayer = pCurLevel->GetLayer(_ChildObject->m_LayerIdx);
				pLayer->DeregisterObjectAsParent(_ChildObject);
			}
		}
	}

	m_vecChildren.push_back(_ChildObject);
	_ChildObject->m_Parent = this;

	qLevelMgr::GetInst()->LevelChanged();
}


bool qGameObject::IsAncestor(qGameObject* _Object)
{
	qGameObject* pObject = m_Parent;

	while (pObject)
	{
		if (pObject == _Object)
			return true;
		else
			pObject = pObject->GetParent();
	}

	return false;
}


void qGameObject::DisconnectWithLayer()
{
	if (nullptr == m_Parent)
	{
		qLevel* pLevel = qLevelMgr::GetInst()->GetCurrentLevel();
		qLayer* pLayer = pLevel->GetLayer(m_LayerIdx);
		pLayer->DisconnectWithObject(this);
	}

	m_LayerIdx = -1;
}

void qGameObject::DeregisterChild()
{
	qLevelMgr::GetInst()->LevelChanged();

	vector<qGameObject*>::iterator iter = m_Parent->m_vecChildren.begin();

	for (; iter != m_Parent->m_vecChildren.end(); ++iter)
	{
		if ((*iter) == this)
		{
			m_Parent->m_vecChildren.erase(iter);
			m_Parent = nullptr;
			return;
		}
	}

	assert(nullptr);
}

void qGameObject::Destroy()
{
	tTask task = {};
	task.Type = TASK_TYPE::DELETE_OBJECT;
	task.Param_0 = (DWORD_PTR)this;

	qTaskMgr::GetInst()->AddTask(task);
}



void qGameObject::Begin()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == m_arrCom[i])
			continue;

		m_arrCom[i]->Begin();
	}

	for (size_t i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->Begin();
	}

	// 자식 오브젝트
	for (size_t i = 0; i < m_vecChildren.size(); ++i)
	{
		m_vecChildren[i]->Begin();
	}
}

void qGameObject::Tick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->Tick();
	}

	for (size_t i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->Tick();
	}

	// 자식 오브젝트
	for (size_t i = 0; i < m_vecChildren.size(); ++i)
	{
		m_vecChildren[i]->Tick();
	}
}

void qGameObject::FinalTick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->FinalTick();
	}
	
	// 레이어 등록
	assert(-1 != m_LayerIdx);
	qLevel* pLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qLayer* pLayer = pLevel->GetLayer(m_LayerIdx);
	pLayer->RegisterGameObject(this);



	// 자식 오브젝트
	vector<qGameObject*>::iterator iter = m_vecChildren.begin();
	for (; iter != m_vecChildren.end(); )
	{
		(*iter)->FinalTick();

		if ((*iter)->IsDead())
			iter = m_vecChildren.erase(iter);
		else
			++iter;
	}
}

void qGameObject::Render()
{
	if (m_RenderCom)
		m_RenderCom->Render();
}

