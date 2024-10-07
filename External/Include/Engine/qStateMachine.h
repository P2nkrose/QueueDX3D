#pragma once
#include "qComponent.h"

#include "qFSM.h"
#include "qBlackboard.h"

class qStateMachine : public qComponent
{
public:
	CLONE(qStateMachine);
	qStateMachine();
	~qStateMachine();

public:
	virtual void Begin() override;
	virtual void FinalTick() override;

	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;


public:
	void SetFSM(Ptr<qFSM> _FSM);



	void AddBlackboardData(const wstring& _strKey, BB_DATA _Type, void* _pData);
	void* GetBlackboardData(const wstring& _strKey);


private:


	qBlackboard     m_Blackboard;
};

