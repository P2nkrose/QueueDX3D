#pragma once
#include "qComponent.h"

#include "qTimeMgr.h"
#include "qKeyMgr.h"
#include "qAssetMgr.h"
#include "components.h"

enum class SCRIPT_PARAM
{
	INT,
	FLOAT,
	VEC2,
	VEC3,
	VEC4,
	TEXTURE,
	PREFAB,
};


struct tScriptParam
{
	SCRIPT_PARAM	Type;
	void*			pData;
	string			Desc;
	DWORD_PTR		Param_0;
	DWORD_PTR		Param_1;
};

class qScript : public qComponent
{
public:
	qScript(UINT _Type);
	~qScript();

	virtual void Begin() override {}
	virtual void Tick() PURE;
	virtual void FinalTick() final override {}

	virtual void SaveToFile(FILE* _File) = 0;
	virtual void LoadFromFile(FILE* _File) = 0;

	virtual void BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider){}
	virtual void Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider){}
	virtual void EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider){}

public:
	qRenderComponent* GetRenderComponent() { return GetOwner()->GetRenderComponent(); }
	UINT GetScriptType() { return m_ScriptType; }
	const vector<tScriptParam>& GetScriptParam() { return m_ScriptParam; }

public:
	void SetDir(DIRECTION _Dir) { m_Dir = _Dir; }
	DIRECTION GetDir() { return m_Dir; }

	tUnitInfo& GetPrevInfo() { return m_PrevUnitInfo; }
	tUnitInfo& GetUnitInfo() { return m_CurUnitInfo; }

	virtual void Hit(float _Damage){}

protected:
	void AddScriptParam(SCRIPT_PARAM _Type, const string& _Desc, void* _pData, DWORD_PTR _Param0 = 0, DWORD_PTR _Param1 = 0)
	{
		m_ScriptParam.push_back(tScriptParam{ _Type, _pData, _Desc, _Param0, _Param1 });
	}

	void Instantiate(Ptr<qPrefab> _Pref, int _LayerIdx, Vec3 _WorldPos, const wstring& _Name = L"");


	tUnitInfo				m_CurUnitInfo;
	tUnitInfo				m_PrevUnitInfo;


private:
	UINT					m_ScriptType;
	vector<tScriptParam>	m_ScriptParam;

	DIRECTION				m_Dir;
};

