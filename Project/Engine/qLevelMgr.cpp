#include "pch.h"
#include "qLevelMgr.h"

#include "qLevel.h"
#include "qLayer.h"
#include "qGameObject.h"

//#include "qLevel_stage1.h"

#include "qTaskMgr.h"






qLevelMgr::qLevelMgr()
	: m_CurLevel(nullptr)
{

}


qLevelMgr::~qLevelMgr()
{
	if (nullptr != m_CurLevel)
		delete m_CurLevel;
}


qGameObject* qLevelMgr::FindObjectByName(const wstring& _Name)
{
	if (m_CurLevel)
	{
		return m_CurLevel->FindObjectByName(_Name);
	}

	return nullptr;
}

void qLevelMgr::LevelChanged()
{
	qTaskMgr::GetInst()->AddTask(tTask{ TASK_TYPE::LEVEL_CHANGED });
}


qLevel* qLevelMgr::GetLevelbyName(wstring _Name)
{
	auto Level = m_Levels.find(_Name);

	if (Level->first == _Name)
	{
		return Level->second;
	}
}

void qLevelMgr::ChangeLevelbyName(std::wstring _Name)
{
	auto Level = m_Levels.find(_Name);

	ChangeLevel(Level->second);
}


void qLevelMgr::InsertLevel(wstring _Name, qLevel* _Level)
{
	// 중복체크
	if (nullptr == _Level)
		return;

	m_Levels.insert(std::make_pair(_Name, _Level));
}




void qLevelMgr::Init()
{
	// 레벨 종류 넣기
	//m_arrLevel[(UINT)LEVEL_TYPE::STAGE1] = new qLevel_stage1;


	//ChangeLevel(m_arrLevel[(UINT)LEVEL_TYPE::STAGE1]);
}

void qLevelMgr::Progress()
{
	m_LevelChanged = false;
	if (nullptr == m_CurLevel)
		return;

	if (m_CurLevel->GetState() == LEVEL_STATE::PLAY)
	{
		m_CurLevel->Tick();
	}

	m_CurLevel->ClearObject();
	m_CurLevel->FinalTick();
}



bool qLevelMgr::ChangeLevel(qLevel* _NextLevel)
{
	if (m_CurLevel == _NextLevel)
		return false;

	if (nullptr != m_CurLevel)
		delete m_CurLevel;

	m_CurLevel = _NextLevel;

	// 레벨이 변경된 이벤트 ON
	LevelChanged();

	return true;
}