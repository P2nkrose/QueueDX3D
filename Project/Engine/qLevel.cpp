#include "pch.h"
#include "qLevel.h"

#include "qLayer.h"
#include "qGameObject.h"

#include "qLevelMgr.h"
#include "qPathMgr.h"

#include "qTransform.h"

qLevel::qLevel()
	: m_Layer{}
	, m_State(LEVEL_STATE::STOP)
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i] = new qLayer(i);
	}
}

qLevel::qLevel(const qLevel& _Origin)
	: qEntity(_Origin)
	, m_Layer{}
	, m_State(LEVEL_STATE::STOP)

{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i] = _Origin.m_Layer[i]->Clone();
	}
}

qLevel::~qLevel()
{
	Delete_Array(m_Layer);
}

void qLevel::Begin()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->Begin();
	}
}

void qLevel::Tick()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->Tick();
	}
}

void qLevel::FinalTick()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->FinalTick();
	}
}

void qLevel::ClearObject()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->ClearObject();
	}
}


void qLevel::AddObject(int LayerIdx, qGameObject* _Object, bool _bMoveChild)
{
	m_Layer[LayerIdx]->AddObject(_Object, _bMoveChild);

	qLevelMgr::GetInst()->LevelChanged();
}


void qLevel::RegisterAsParent(int LayerIdx, qGameObject* _Object)
{
	m_Layer[LayerIdx]->RegisterAsParent(_Object);
}



qGameObject* qLevel::FindObjectByName(const wstring& _Name)
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		const vector<qGameObject*>& vecParent = m_Layer[i]->GetParentObjects();

		static list<qGameObject*> list;
		for (size_t i = 0; i < vecParent.size(); ++i)
		{
			list.clear();
			list.push_back(vecParent[i]);

			while (!list.empty())
			{
				qGameObject* pObject = list.front();
				list.pop_front();

				const vector<qGameObject*>& vecChild = pObject->GetChildren();
				for (size_t i = 0; i < vecChild.size(); ++i)
				{
					list.push_back(vecChild[i]);
				}

				if (_Name == pObject->GetName())
				{
					return pObject;
				}
			}
		}
	}

	return nullptr;
}

void qLevel::SavePlatform(const wstring& _strRelativePath)
{
	wstring strFullPath = qPathMgr::GetInst()->GetContentPath();
	if (STAGE_NAME::STAGE1 == m_StageName)
	{
		strFullPath += L"edit\\stage1\\";
	}
	else if (STAGE_NAME::STAGE2 == m_StageName)
	{
		strFullPath += L"edit\\stage2\\";
	}
	else if (STAGE_NAME::BOSS == m_StageName)
	{
		strFullPath += L"edit\\boss\\";
	}

	strFullPath += _strRelativePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFullPath.c_str(), L"wb");

	if (nullptr == pFile)
	{
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"파일 저장 실패", L"Error", MB_OK);
		return;
	}

	// Platform 레이어에 해당하는 객체들을 가져옴
	qLayer* platformLayer = m_Layer[2];
	const vector<qGameObject*>& objects = platformLayer->GetObjects();

	// 객체 수를 파일에 저장
	size_t len = objects.size();

	fwrite(&len, sizeof(size_t), 1, pFile);

	// 각 객체의 위치와 크기를 파일에 저장
	for (size_t i = 0; i < objects.size(); ++i)
	{
		Vec3 vPos = objects[i]->Transform()->GetRelativePos();
		Vec3 vScale = objects[i]->Transform()->GetRelativePos();

		fwrite(&vPos, sizeof(Vec3), 1, pFile);
		fwrite(&vScale, sizeof(Vec3), 1, pFile);
	}

	fclose(pFile);
}


void qLevel::LoadPlatform(const wstring& _strRelativePath)
{
	wstring strFullPath = qPathMgr::GetInst()->GetContentPath();

	if (L"stage1" == GetName())
	{
		strFullPath += L"edit\\stage1\\";
	}
	else if (L"stage2" == GetName())
	{
		strFullPath += L"edit\\stage2\\";
	}
	else if (L"boss" == GetName())
	{
		strFullPath += L"edit\\boss\\";
	}

	strFullPath += _strRelativePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFullPath.c_str(), L"rb");

	if (nullptr == pFile)
		return;

	size_t len = 0;

	fread(&len, sizeof(size_t), 1, pFile);

	qLayer* platformLayer = m_Layer[2];

	for (size_t i = 0; i < len; ++i)
	{
		Vec3 vPos;
		Vec3 vScale;

		fread(&vPos, sizeof(Vec3), 1, pFile);
		fread(&vPos, sizeof(Vec3), 1, pFile);

		// 새로운 qGameObject 생성 및 설정
		qGameObject* pPlatform = new qGameObject;
		pPlatform->Transform()->SetRelativePos(vPos);
		pPlatform->Transform()->SetRelativeScale(vScale);

		// 레이어에 추가
		AddObject(2, pPlatform);
	}

	fclose(pFile);
}



void qLevel::ChangeState(LEVEL_STATE _NextState)
{
	if (m_State == _NextState)
		return;

	// Stop -> Pause (X)
	if (STOP == m_State && PAUSE == _NextState)
		return;

	// Stop -> Play (정지 상태의 레벨이 시작되면, 레벨에 있던 물체들은 Begin 이 호출되어야 한다.)
	if (STOP == m_State && PLAY == _NextState)
	{
		m_State = _NextState;
		Begin();
	}
	else
	{
		m_State = _NextState;
	}

	// Play -> Stop (최초 레벨이 시작되던 시점으로 복구가 가능해야 한다.)
}
