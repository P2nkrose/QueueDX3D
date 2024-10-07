#pragma once
#include "qComponent.h"

typedef void(*CALL_BACK)(void);
typedef void(qGameObject::* DELEGATE)(void);

class qRigidBody : public qComponent
{
public:
	CLONE(qRigidBody);

	qRigidBody();
	qRigidBody(const qRigidBody& _Origin);
	~qRigidBody();


public:
	virtual void FinalTick() override;
	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;


public:
	void AddForce(Vec3 _vForce) { m_Force += _vForce; }						// 힘 추가

	void SetMass(float _Mass) { m_Mass = _Mass; }							// 질량 설정
	void SetInitialWalkSpeed(float _Speed) { m_InitWalkSpeed = _Speed; }	// 초기 이동속도 설정
	void SetMaxWalkSpeed(float _Speed) { m_MaxWalkSpeed = _Speed; }			// 최대 이동속도 설정
	void SetMaxGravitySpeed(float _Speed) { m_MaxGravitySpeed = _Speed; }	// 최대 중력가속도 설정
	void SetFriction(float _Friction) { m_Friction = _Friction; }
	void SetJumpSpeed(float _Speed) { m_JumpSpeed = _Speed; }

	void jump();
	void doublejump();

	float GetMass() { return m_Mass; }
	float GetInitWalkSpeed() { return m_InitWalkSpeed; }
	float GetMaxWalkSpeed() { return m_MaxWalkSpeed; }
	float GetFriction() { return m_Friction; }
	Vec3  GetGravityVelocity() { return m_VelocityByGravity; }


	void SetGroundFunc(void(*_pFunc)(void)) { m_GroundFunc = _pFunc; }
	void SetAirFunc(void(*_pFunc)(void)) { m_AirFunc = _pFunc; }


	void SetGroundDelegate(qGameObject* _Inst, DELEGATE _MemFunc)
	{
		m_GroundInst = _Inst;
		m_GroundDelegate = _MemFunc;
	}

	void SetAirDelegate(qGameObject* _Inst, DELEGATE _MemFunc)
	{
		m_AirInst = _Inst;
		m_AirDelegate = _MemFunc;
	}


	void UseGravity(bool _Use)
	{
		m_UseGravity = _Use;
		if (!m_UseGravity)
			m_VelocityByGravity = Vec3(0.f, 0.f, 0.f);
	}

	void SetGround(bool _Ground)
	{
		m_Ground = _Ground;

		if (m_Ground)
		{
			m_VelocityByGravity = Vec3(0.f, 0.f, 0.f);

			if (nullptr != m_GroundFunc)
				m_GroundFunc();

			if (m_GroundInst && m_GroundDelegate)
				(m_GroundInst->*m_GroundDelegate)();
		}
		else
		{
			if (nullptr != m_AirFunc)
				m_AirFunc();

			if (m_AirInst && m_AirDelegate)
				(m_AirInst->*m_AirDelegate)();
		}
	}

	void SetWall(bool _Wall)
	{
		if (m_Wall == _Wall)
		{
			return;
		}

		m_Wall = _Wall;
	}



	bool IsGround() { return m_Ground; }
	bool IsWall() { return m_Wall; }


public:
	void SetVelocityX(float _XSpeed) { m_Velocity.x = _XSpeed; }



private:
	Vec3				m_Velocity;				// 속도 (방향, 크기정보를 갖고 있다. 그래서 vector 라 부른다.
	Vec3				m_VelocityByGravity;	// 중력에 의해서 증가하는 속도
	Vec3				m_AddVelocity;			// 최종 속도에 누적될 속도

	float				m_Mass;					// 질량
	Vec3				m_Force;				// 힘

	float				m_InitWalkSpeed;		// 최소 보장 속력
	float				m_MaxWalkSpeed;			// 최대 제한 속력
	float				m_MaxGravitySpeed;		// 중력으로 발생한 낙하속도 제한

	float				m_Friction;				// 마찰력

	float				m_GravityAccel;			// 중력 가속도
	bool				m_UseGravity;			// 중력 사용 <-> 미사용 bool
	bool				m_Ground;				// 땅 위에 서있는지 체크
	bool				m_Wall;					// 벽에 부딪혔는지 체크

	float				m_JumpSpeed;			// 점프 속력
	float				m_DoubleJumpSpeed;		// 더플점프 속력




	// Ground, Air, Rope   On / Off 호출시킬 함수포인터
	CALL_BACK			m_GroundFunc;
	CALL_BACK			m_AirFunc;

	// Delegate
	qGameObject*		m_GroundInst;
	DELEGATE			m_GroundDelegate;

	qGameObject*		m_AirInst;
	DELEGATE			m_AirDelegate;
};

