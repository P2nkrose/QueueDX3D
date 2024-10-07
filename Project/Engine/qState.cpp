#include "pch.h"
#include "qState.h"

#include "qFSM.h"



qState::qState(UINT _StateType)
	: m_Owner(nullptr)
	, m_StateType(_StateType)
{
}

qState::~qState()
{
}

void qState::ChangeState(const wstring& _strStateName)
{
	m_Owner->ChangeState(_strStateName);
}




