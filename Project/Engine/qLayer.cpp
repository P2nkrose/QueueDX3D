#include "pch.h"
#include "qLayer.h"

#include "qGameObject.h"

qLayer::qLayer(int _LayerIdx)
	: m_LayerIdx(_LayerIdx)
{
}

qLayer::qLayer(const qLayer& _Origin)
	: qEntity(_Origin)
	, m_LayerIdx(_Origin.m_LayerIdx)
{
	for (size_t i = 0; i < _Origin.m_Parents.size(); ++i)
	{
		AddObject(_Origin.m_Parents[i]->Clone(), false);
	}
}

qLayer::~qLayer()
{
	Delete_Vec(m_Parents);
}

void qLayer::Begin()
{
	for (size_t i = 0; i < m_Parents.size(); ++i)
	{
		m_Parents[i]->Begin();
	}
}

void qLayer::Tick()
{
	for (size_t i = 0; i < m_Parents.size(); ++i)
	{
		m_Parents[i]->Tick();
	}
}

void qLayer::FinalTick()
{
	vector<qGameObject*>::iterator iter = m_Parents.begin();

	for (; iter != m_Parents.end(); )
	{
		(*iter)->FinalTick();

		if ((*iter)->IsDead())
			iter = m_Parents.erase(iter);
		else
			++iter;
	}
}

void qLayer::AddObject(qGameObject* _Object, bool _bMoveChild)
{
	// 1. 오브젝트가 다른 레이어 소속인 경우
	if (-1 != _Object->GetLayerIdx())
	{
		assert(_Object->GetLayerIdx() != m_LayerIdx);

		// 기존에 소속된 레이어에서 빠져나와야 한다.
		_Object->DisconnectWithLayer();
	}

	// 2. 최상위 오브젝트인 경우
	if (nullptr == _Object->GetParent())
	{
		m_Parents.push_back(_Object);
	}

	// 자식들까지 이동시킬지 말지
	static list<qGameObject*> queue;
	queue.clear();
	queue.push_back(_Object);
	_Object->m_LayerIdx = m_LayerIdx;

	while (!queue.empty())
	{
		qGameObject* pObject = queue.front();
		queue.pop_front();

		if (_bMoveChild || pObject->m_LayerIdx == -1)
		{
			pObject->m_LayerIdx = m_LayerIdx;
		}

		const vector<qGameObject*>& vecChildren = pObject->GetChildren();
		for (size_t i = 0; i < vecChildren.size(); ++i)
		{
			queue.push_back(vecChildren[i]);
		}
	}

}

void qLayer::DisconnectWithObject(qGameObject* _Object)
{
	vector<qGameObject*>::iterator iter = m_Parents.begin();

	for (; iter != m_Parents.end(); ++iter)
	{
		if (_Object == (*iter))
		{
			m_Parents.erase(iter);
			return;
		}
	}

	assert(nullptr);
}

void qLayer::RegisterAsParent(qGameObject* _Object)
{
	assert(_Object->GetLayerIdx() == m_LayerIdx && !_Object->GetParent());

	m_Parents.push_back(_Object);
	return;
}

void qLayer::DeregisterObjectAsParent(qGameObject* _Object)
{
	vector<qGameObject*>::iterator iter = m_Parents.begin();

	for (; iter != m_Parents.end(); ++iter)
	{
		if (_Object == (*iter))
		{
			m_Parents.erase(iter);
			return;
		}
	}

	assert(nullptr);
}

void qLayer::DeregisterObject(qGameObject* _Object)
{
	assert(_Object->m_LayerIdx == m_LayerIdx);

	_Object->m_LayerIdx = -1;

	if (nullptr == _Object->GetParent())
	{
		vector<qGameObject*>::iterator iter = m_Parents.begin();

		for (; iter != m_Parents.end(); ++iter)
		{
			if (_Object == (*iter))
			{
				m_Parents.erase(iter);
				return;
			}
		}

		assert(nullptr);

	}
}


