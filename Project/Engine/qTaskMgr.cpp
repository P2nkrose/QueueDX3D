#include "pch.h"
#include "qTaskMgr.h"

#include "qLevelMgr.h"
#include "qLevel.h"
#include "qLayer.h"
#include "qGameObject.h"
#include "qCollider2D.h"

#include "qAssetMgr.h"

#include "qAsset.h"


qTaskMgr::qTaskMgr()
{}

qTaskMgr::~qTaskMgr()
{}

void qTaskMgr::Tick()
{
	ClearGC();

	ExecuteTask();
}

void qTaskMgr::AddTask(const tTask& _Task)
{
	m_vecTask.push_back(_Task);
}

void qTaskMgr::ClearGC()
{
	Delete_Vec(m_GC);
}

void qTaskMgr::ExecuteTask()
{
	for (size_t i = 0; i < m_vecTask.size(); ++i)
	{
		tTask& task = m_vecTask[i];
		switch (task.Type)
		{
		case TASK_TYPE::CREATE_OBJECT:
		{
			qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
			int LayerIndex = (int)task.Param_0;
			qGameObject* pObject = (qGameObject*)task.Param_1;
			pCurLevel->AddObject(LayerIndex, pObject);

			if (pCurLevel->GetState() != STOP)
			{
				pObject->Begin();
			}
		}
		break;

		case TASK_TYPE::DELETE_OBJECT:
		{
			qGameObject* pObject = (qGameObject*)task.Param_0;
			if (pObject->m_Dead)
				continue;

			// GC¿¡ ³Ö±â
			pObject->m_Dead = true;
			m_GC.push_back(pObject);
		}
		break;

		case TASK_TYPE::CHANGE_LEVELSTATE:
		{
			LEVEL_STATE NextState = (LEVEL_STATE)task.Param_0;
			qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
			pCurLevel->ChangeState(NextState);
		}
		break;

		case TASK_TYPE::CHANGE_LEVEL:
		{
			// Param_0 : Level Adress, Param_1 : Level State
			qLevel* pLevel = (qLevel*)task.Param_0;
			LEVEL_STATE NextState = (LEVEL_STATE)task.Param_1;

			qLevelMgr::GetInst()->ChangeLevel(pLevel);
			pLevel->ChangeState(NextState);
		}
		break;

		case TASK_TYPE::ASSET_CHANGED:
		{
			qAssetMgr::GetInst()->m_Changed = true;
		}
		break;

		case TASK_TYPE::LEVEL_CHANGED:
		{
			qLevelMgr::GetInst()->m_LevelChanged = true;
		}
		break;

		case TASK_TYPE::DEL_ASSET:
		{
			qAsset* pAsset = (qAsset*)task.Param_0;
			ASSET_TYPE Type = pAsset->GetAssetType();
			qAssetMgr::GetInst()->DeleteAsset(Type, pAsset->GetKey());
		}
		break;

		case TASK_TYPE::COLLIDER2D_SEMI_DEACTIVE:
		{
			qCollider2D* pCollider = (qCollider2D*)m_vecTask[i].Param_0;
			pCollider->m_SemiDeactive = true;
		}
		break;

		case TASK_TYPE::COLLIDER2D_DEACTIVE:
		{
			qCollider2D* pCollider = (qCollider2D*)m_vecTask[i].Param_0;
			pCollider->m_SemiDeactive = false;
			pCollider->m_Active = false;
		}
		break;
		}
	}

	m_vecTask.clear();	
}