#pragma once
class qLevelSaveLoad
{
public:
	static void SaveLevel(const wstring& _FilePath, qLevel* _Level);
	static void SaveGameObject(FILE* _File, qGameObject* _Object);

	static class qLevel* LoadLevel(const wstring& _FilePath);
	static class qGameObject* LoadGameObject(FILE* _File);
	static class qComponent* GetComponent(COMPONENT_TYPE _Type);
};

