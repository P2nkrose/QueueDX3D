#pragma once
#include "qEntity.h"
#include "qGameObject.h"

#define GET_OTHER_COMPONENT(Type) q##Type* Type() { return m_Owner->Type(); }

class qComponent : public qEntity
{
public:
	friend class qGameObject;

	virtual qComponent* Clone() = 0;
	qComponent(COMPONENT_TYPE _Type);
	qComponent(const qComponent& _Origin);
	~qComponent();

	virtual void Init() {}
	virtual void Begin();
	virtual void Tick();
	virtual void FinalTick() = 0;

public:
	virtual void SaveToFile(FILE* _File) = 0;		// 파일에 컴포넌트의 정보를 저장
	virtual void LoadFromFile(FILE* _File) = 0;		// 파일에 컴포넌트의 정보를 로드

public:
	COMPONENT_TYPE GetComponentType() { return m_Type; }
	qGameObject* GetOwner() { return m_Owner; }

	GET_OTHER_COMPONENT(Transform);
	GET_OTHER_COMPONENT(MeshRender);
	GET_OTHER_COMPONENT(Camera);
	GET_OTHER_COMPONENT(Collider2D);
	GET_OTHER_COMPONENT(FlipBookComponent);
	GET_OTHER_COMPONENT(TileMap);
	GET_OTHER_COMPONENT(Light2D);
	GET_OTHER_COMPONENT(Light3D);
	GET_OTHER_COMPONENT(ParticleSystem);
	GET_OTHER_COMPONENT(RigidBody);
	GET_OTHER_COMPONENT(FSM);
	GET_OTHER_COMPONENT(SkyBox);
	GET_OTHER_COMPONENT(Decal);
	GET_OTHER_COMPONENT(LandScape);
	
	

private:
	void SetOwner(qGameObject* _Object) { m_Owner = _Object; }


private:
	const COMPONENT_TYPE	m_Type;
	qGameObject*			m_Owner;
};

