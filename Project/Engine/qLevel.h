#pragma once
#include "qEntity.h"

class qLayer;
class qCollider2D;
class qGameObject;

class qLevel : public qEntity
{
public:
	friend class qTaskMgr;
	friend class qLevelMgr;

	CLONE(qLevel);

	//virtual qLevel* Clone() { return new qLevel(*this); }
	qLevel();
	qLevel(const qLevel& _Origin);
	~qLevel();

public:
	virtual void Begin();		// 레벨이 시작되는 순간 or 레벨에 추가(합류) 하는 순간
	virtual void Tick();
	virtual void FinalTick();


	void ClearObject();

public:
	void AddObject(int LayerIdx, qGameObject* _Object, bool _bMoveChild = false);
	void RegisterAsParent(int LayerIdx, qGameObject* _Object);

	qLayer* GetLayer(int _LayerIdx) { return m_Layer[_LayerIdx]; }
	LEVEL_STATE GetState() { return m_State; }

	qGameObject* FindObjectByName(const wstring& _Name);


public:
	void SetStageName(STAGE_NAME _Name) { m_StageName = _Name; }


protected:
	void SavePlatform(const wstring& _strRelativePath);
	void LoadPlatform(const wstring& _strRelativePath);


private:
	void ChangeState(LEVEL_STATE _NextState);


private:
	qLayer*			m_Layer[MAX_LAYER];
	

	LEVEL_STATE		m_State;
	STAGE_NAME		m_StageName;
};

