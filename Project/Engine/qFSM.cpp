#include "pch.h"
#include "qFSM.h"

#include <States/qStateMgr.h>

#include "qPathMgr.h"
#include "qTaskMgr.h"


#include "qState.h"

qFSM::qFSM()
	: qComponent(COMPONENT_TYPE::STATEMACHINE)
	, m_CurState(nullptr)
	, m_PrevState(nullptr)
{

}

qFSM::qFSM(const qFSM& _Other)
	: qComponent(_Other)
	, m_CurState(nullptr)
	, m_PrevState(nullptr)
{
}

qFSM::~qFSM()
{
	Delete_Map(m_mapState);
}

void qFSM::Begin()
{
}

void qFSM::FinalTick()
{
	if (nullptr == m_CurState)
		return;

	m_CurState->m_Owner = this;
	m_CurState->FinalTick();
}

void qFSM::AddState(const wstring& _strStateName, qState* _State)
{
	assert(!(FindState(_strStateName)));

	_State->m_Owner = this;
	m_mapState.insert(make_pair(_strStateName, _State));
}

void qFSM::DeleteState(const wstring& _StateKey)
{
	qState* pState = FindState(_StateKey);

	if (pState == nullptr)
	{
		MessageBoxA(nullptr, "해당 키를 가진 스테이트가 없습니다.", "Delete State Failed", MB_OK);
		return;
	}

	delete pState;
	m_mapState.erase(_StateKey);
}

qState* qFSM::FindState(const wstring& _strStateName)
{
	map<wstring, qState*>::iterator iter = m_mapState.find(_strStateName);

	if (iter == m_mapState.end())
		return nullptr;

	return iter->second;
}


//void qFSM::SetBlackboardData(const wstring& _DataKey, BB_DATA _Type, void* _pData)
//{
//	m_Blackboard->SetBlackboardData(_DataKey, _Type, _pData);
//}
//
//
//void* qFSM::GetBlackboardData(const wstring& _strKey)
//{
//	return m_Blackboard->GetBlackboardData(_strKey);
//}

void qFSM::ChangeState_proc(qState* _pNextState)
{
	if (m_CurState)
	{
		m_CurState->m_Owner= this;
		m_CurState->Exit();
	}

	m_PrevState = m_CurState;
	m_CurState = _pNextState;
	m_CurState->m_Owner = this;
	m_CurState->Enter();
}


void qFSM::ChangeState(const wstring& _strNextStateName)
{
	if (m_CurState && (_strNextStateName == m_CurState->GetName()))
		return;

	if (nullptr != m_CurState)
		m_CurState->Exit();

	m_CurState = FindState(_strNextStateName);

	assert(m_CurState);

	m_CurState->Enter();
}



int qFSM::Save(const wstring& _strRelativePath)
{
	wstring strFilePath = qPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	// State의 개수 저장
	size_t StateCount = m_mapState.size();
	fwrite(&StateCount, sizeof(size_t), 1, pFile);

	// State 저장
	map<wstring, qState*>::iterator iter = m_mapState.begin();

	for (; iter != m_mapState.end(); ++iter)
	{
		// State Key 저장
		SaveWString(iter->first, pFile);

		// State Name 저장
		wstring StrName = qStateMgr::GetStateName(iter->second);

		SaveWString(StrName, pFile);

		iter->second->SaveToFile(pFile);
	}

	fclose(pFile);

	return S_OK;
}

int qFSM::Load(const wstring& _strFilePath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"rb");

	if (nullptr == pFile)
		return E_FAIL;

	// State 개수 로드
	size_t StateCount = 0;
	fread(&StateCount, sizeof(size_t), 1, pFile);

	// 스테이트 로드
	for (size_t i = 0; i < StateCount; ++i)
	{
		// 스테이트 키 로드
		wstring StateKey;
		LoadWString(StateKey, pFile);

		// 스테이트 Name 로드
		wstring StateName;
		LoadWString(StateName, pFile);

		// 스테이트 생성
		qState* pState = qStateMgr::GetState(StateName);
		pState->LoadFromFile(pFile);

		pState->m_Owner = this;
		m_mapState.insert(make_pair(StateKey, pState));
	}

	fclose(pFile);

	return S_OK;
}

void qFSM::SaveToFile(FILE* _File)
{
}

void qFSM::LoadFromFile(FILE* _File)
{
}



