#include "pch.h"
#include "qLevelSaveLoad.h"

#include <Engine/qLevelMgr.h>
#include <Engine/qLevel.h>
#include <Engine/qLayer.h>
#include <Engine/qGameObject.h>
#include <Engine/components.h>

#include <Scripts/qScriptMgr.h>


void qLevelSaveLoad::SaveLevel(const wstring& _FilePath, qLevel* _Level)
{

	assert(_Level && _Level->GetState() == LEVEL_STATE::STOP);

	FILE* File = nullptr;
	_wfopen_s(&File, _FilePath.c_str(), L"wb");

	// Level 이름 저장
	SaveWString(_Level->GetName(), File);

	// Level 안에 있는 Layer 를 저장
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		qLayer* pLayer = _Level->GetLayer(i);

		// Layer 이름 저장
		SaveWString(pLayer->GetName(), File);

		// Layer 안에 있는 GameObject 를 저장
		const vector<qGameObject*>& vecParents = pLayer->GetParentObjects();

		// Layer 가 보유한 ParentObject 개수 저장
		size_t count = vecParents.size();
		fwrite(&count, sizeof(size_t), 1, File);

		// GameObject 저장
		for (size_t i = 0; i < vecParents.size(); ++i)
		{
			SaveGameObject(File, vecParents[i]);
		}
	}

	fclose(File);
}

void qLevelSaveLoad::SaveGameObject(FILE* _File, qGameObject* _Object)
{
	// GameObject 의 이름 저장
	SaveWString(_Object->GetName(), _File);

	// Component의 정보 저장
	UINT i = 0;
	for (; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		qComponent* pComponent = _Object->GetComponent((COMPONENT_TYPE)i);

		if (nullptr == pComponent)
			continue;

		// Component Type 을 저장
		COMPONENT_TYPE Type = pComponent->GetComponentType();
		fwrite(&Type, sizeof(COMPONENT_TYPE), 1, _File);

		pComponent->SaveToFile(_File);
	}

	// COMPONENT_TYPE::END 저장
	fwrite(&i, sizeof(COMPONENT_TYPE), 1, _File);

	// Script 정보 저장
	// Script 개수 저장
	const vector<qScript*> vecScripts = _Object->GetScripts();
	size_t ScriptCount = vecScripts.size();
	fwrite(&ScriptCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < ScriptCount; ++i)
	{
		// Script 의 이름 저장
		wstring ScriptName = qScriptMgr::GetScriptName(vecScripts[i]);
		SaveWString(ScriptName, _File);

		// Script 정보 저장
		vecScripts[i]->SaveToFile(_File);
	}

	// Child 정보 저장
	const vector<qGameObject*>& vecChild = _Object->GetChildren();
	size_t ChildCount = vecChild.size();
	fwrite(&ChildCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		SaveGameObject(_File, vecChild[i]);
	}

}

qLevel* qLevelSaveLoad::LoadLevel(const wstring& _FilePath)
{
	FILE* File = nullptr;
	_wfopen_s(&File, _FilePath.c_str(), L"rb");
	
	// Level 생성
	qLevel* pNewLevel = new qLevel;

	// Level 이름 불러오기
	wstring LevelName;
	LoadWString(LevelName, File);
	pNewLevel->SetName(LevelName);

	// Level 안에 있는 Layer 정보 불러오기
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		qLayer* pLayer = pNewLevel->GetLayer(i);
		
		// Layer 이름 불러오기
		wstring LayerName;
		LoadWString(LayerName, File);
		pLayer->SetName(LayerName);

		// Layer 가 보유한 ParentObject 개수 불러오기
		size_t count = 0;
		fread(&count, sizeof(size_t), 1, File);

		// GameObject 불러와서 Layer 에 집어넣기
		for (size_t i = 0; i < count; ++i)
		{
			qGameObject* pLoadedObject = LoadGameObject(File);
			pLayer->AddObject(pLoadedObject, false);
		}
	}

	fclose(File);
	
	return pNewLevel;
}

qGameObject* qLevelSaveLoad::LoadGameObject(FILE* _File)
{
	qGameObject* pObject = new qGameObject;

	// GameObject 의 이름 로드
	wstring Name;
	LoadWString(Name, _File);
	pObject->SetName(Name);

	// Component 정보 로드
	COMPONENT_TYPE Type = COMPONENT_TYPE::END;
	while (true)
	{
		// 저장되어 있는 정보가 어떤 컴포넌트인지 확인
		fread(&Type, sizeof(COMPONENT_TYPE), 1, _File);

		// 읽은 타입 정보가 END 인 경우, 저장된 컴포넌트 정보의 끝이다.
		if (COMPONENT_TYPE::END == Type)
			break;

		// 저장된 타입에 맞는 컴포넌트를 생성 시키고, 저장할 때랑 동일한 순서로 데이터를 읽는다.
		qComponent* pComponent = GetComponent(Type);

		// 생성된 컴포넌트를 오브젝트에 넣어준다.
		pObject->AddComponent(pComponent);

		// 저장 당시의 정보를 읽어와서 복구한다.
		pComponent->LoadFromFile(_File);
	}

	// Script 정보 로드
	size_t ScriptCount = 0;
	fread(&ScriptCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < ScriptCount; ++i)
	{
		// Script 의 이름 읽기
		wstring ScriptName;
		LoadWString(ScriptName, _File);

		// 읽은 Script 이름으로 이름에 해당하는 Script 생성
		qScript* pScript = qScriptMgr::GetScript(ScriptName);
		pScript->LoadFromFile(_File);

		pObject->AddComponent(pScript);
	}

	// Child 정보 로드
	size_t ChildCount = 0;
	fread(&ChildCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < ChildCount; ++i)
	{
		qGameObject* pChildObject = LoadGameObject(_File);
		pObject->AddChild(pChildObject);
	}

	return pObject;
}

qComponent* qLevelSaveLoad::GetComponent(COMPONENT_TYPE _Type)
{
	switch (_Type)
	{
	case COMPONENT_TYPE::TRANSFORM:
		return new qTransform;

	case COMPONENT_TYPE::COLLIDER2D:
		return new qCollider2D;

	case COMPONENT_TYPE::COLLIDER3D:

		break;
	case COMPONENT_TYPE::LIGHT2D:
		return  new qLight2D;

	case COMPONENT_TYPE::LIGHT3D:
		return new qLight3D;

	case COMPONENT_TYPE::FLIPBOOKCOMPONENT:
		return new qFlipBookComponent;

	case COMPONENT_TYPE::ANIMATOR3D:
		break;

	case COMPONENT_TYPE::STATEMACHINE:
		return new qFSM;

	case COMPONENT_TYPE::RIGIDBODY:
		return new qRigidBody;

	case COMPONENT_TYPE::CAMERA:
		return  new qCamera;

	case COMPONENT_TYPE::MESHRENDER:
		return  new qMeshRender;

	case COMPONENT_TYPE::TILEMAP:
		return  new qTileMap;

	case COMPONENT_TYPE::PARTICLESYSTEM:
		return new qParticleSystem;
		
	case COMPONENT_TYPE::DECAL:
		return new qDecal;

	case COMPONENT_TYPE::SKYBOX:
		return new qSkyBox;

	case COMPONENT_TYPE::LANDSCAPE:
		break;
	}

	return nullptr;
}
