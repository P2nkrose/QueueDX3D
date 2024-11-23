#pragma once
#include "pch.h"
#include "qEntity.h"

class qComponent;
class qRenderComponent;
class qScript;

#define GET_COMPONENT(Type, TYPE) class q##Type* Type() { return (q##Type*)GetComponent(COMPONENT_TYPE::TYPE); }


class qGameObject : public qEntity
{
public:

	friend class qLevel;
	friend class qLayer;
	friend class qTaskMgr;

	CLONE(qGameObject);
	qGameObject();
	qGameObject(const qGameObject& _Origin);
	~qGameObject();

	void Begin();
	void Tick();
	virtual void FinalTick();
	void Render();

public:
	void AddComponent(qComponent* _Component);
	qComponent* GetComponent(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }
	qRenderComponent* GetRenderComponent() { return m_RenderCom; }

	qGameObject* GetParent() { return m_Parent; }
	qGameObject* GetChild(const wstring& _ChildName);

	int GetLayerIdx() { return m_LayerIdx; }
	
public:
	void AddChild(qGameObject* _ChildObject);
	const vector<qGameObject*>& GetChildren() { return m_vecChildren; }
	const vector<qScript*> GetScripts() { return m_vecScript; }

	bool IsAncestor(qGameObject* _Object);
	bool IsDead() { return m_Dead; }

	void DisconnectWithLayer();

	// Unregister : 등록을 취소하다, 등록하는 행위를 취소하다.
	// Deregister : 등록된 것을 취소하다.
	void DeregisterChild();

	void Destroy();


public:
	template<typename T>
	T* GetScript()
	{
		for (size_t i = 0; i < m_vecScript.size(); ++i)
		{
			if (dynamic_cast<T*>(m_vecScript[i]))
				return (T*)m_vecScript[i];
		}
		return nullptr;
	}



public:

	GET_COMPONENT(Transform, TRANSFORM);
	GET_COMPONENT(MeshRender, MESHRENDER);
	GET_COMPONENT(Camera, CAMERA);
	GET_COMPONENT(Collider2D, COLLIDER2D);
	GET_COMPONENT(FlipBookComponent, FLIPBOOKCOMPONENT);
	GET_COMPONENT(TileMap, TILEMAP);
	GET_COMPONENT(Light2D, LIGHT2D);
	GET_COMPONENT(Light3D, LIGHT3D);
	GET_COMPONENT(ParticleSystem, PARTICLESYSTEM);
	GET_COMPONENT(RigidBody, RIGIDBODY);
	GET_COMPONENT(Script, SCRIPT);
	GET_COMPONENT(SkyBox, SKYBOX);
	GET_COMPONENT(Decal, DECAL);
	GET_COMPONENT(LandScape, LANDSCAPE);


private:

	qComponent*				m_arrCom[(UINT)COMPONENT_TYPE::END];
	qRenderComponent*		m_RenderCom;
	vector<qScript*>		m_vecScript;

	qGameObject*			m_Parent;
	vector<qGameObject*>	m_vecChildren;

	int						m_LayerIdx;		// 소속 레이어의 인덱스 번호

	bool					m_Dead;
};

