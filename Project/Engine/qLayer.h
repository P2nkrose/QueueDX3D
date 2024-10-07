#pragma once
#include "qEntity.h"

class qGameObject;

class qLayer : public qEntity
{
public:
	CLONE(qLayer);
	qLayer(int _LayerIdx);
	qLayer(const qLayer& _Origin);
	~qLayer();

public:
	
	void Begin();
	void Tick();
	void FinalTick();


public:
	int GetLayerIdx() { return m_LayerIdx; }
	void AddObject(qGameObject* _Object, bool _bMoveChild);
	
	const vector<qGameObject*>& GetParentObjects() { return m_Parents; }
	const vector<qGameObject*>& GetObjects() { return m_Objects; }

	void ClearObject() { m_Objects.clear(); }
	void RegisterGameObject(qGameObject* _Object) { m_Objects.push_back(_Object); }
	void DisconnectWithObject(qGameObject* _Object);

	void RegisterAsParent(qGameObject* _Object);
	void DeregisterObjectAsParent(qGameObject* _Object);
	void DeregisterObject(qGameObject* _Object);


private:
	vector<qGameObject*>	m_Parents;	// 해당 레이어 소속 오브젝트중에서 최상위 부모 오브젝트만 관리
	vector<qGameObject*>	m_Objects;	// 해당 레이어 소속 오브젝트 중에서 부모 자식 상관없는 모든 오브젝트

	const int				m_LayerIdx;
};

