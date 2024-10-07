#pragma once
#include "qComponent.h"



class qStateMachine;
class qState;

class qFSM : public qComponent
{
public:
	friend class qTaskMgr;
    CLONE(qFSM);

    qFSM();
	qFSM(const qFSM& _Other);
    ~qFSM();

public:
	virtual void Begin() override;
	virtual void FinalTick() override;


public:
	qState* FindState(const wstring& _strStateName);
	void AddState(const wstring& _strStateName, qState* _State);
	void DeleteState(const wstring& _StateKey);
	void ChangeState(const wstring& _strNextStateName);

	virtual int Save(const wstring& _strRelativePath);
	virtual int Load(const wstring& _strFilePath);

	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;

public:
	qState* GetCurState() { return m_CurState; }
	const map<wstring, qState*>& GetStates() { return m_mapState; }
	void SetState(const wstring& _strState) { m_CurState = FindState(_strState); }

//public:
//	void SetBlackboardData(const wstring& _DataKey, BB_DATA _Type, void* _pData);
//	void* GetBlackboardData(const wstring& _strKey);


private:
	void ChangeState_proc(qState* _pNextState);

private:
	map<wstring, qState*>	m_mapState;
	
	qState*					m_CurState;
	qState*					m_PrevState;
};


