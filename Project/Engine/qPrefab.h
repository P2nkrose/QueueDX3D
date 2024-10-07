#pragma once
#include "qAsset.h"

#include "qEngine.h"

class qPrefab : public qAsset
{
public:
	friend class qEngine;

	qPrefab();
	~qPrefab();

public:
	void SetProtoObject(qGameObject* _Object) { m_ProtoObject = _Object; }
	qGameObject* Instantiate();

public:
	virtual int Save(const wstring& _FilePath) override;
	virtual int Load(const wstring& _FilePath) override;


private:
	class qGameObject*		m_ProtoObject;

	static OBJECT_SAVE		g_ObjectSaveFunc;
	static OBJECT_LOAD		g_ObjectLoadFunc;

};

