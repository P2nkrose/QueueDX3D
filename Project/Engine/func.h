#pragma once

void CreateObject(class qGameObject* _NewObject, int _LayerIndex);
void DeleteObject(qGameObject* _DeleteObject);
void ChangeLevelState(LEVEL_STATE _NextState);
void ChangeLevel(class qLevel* _Level, LEVEL_STATE _NextLevelState);

bool IsVaild(qGameObject*& _Object);

void DrawDebugRect(Vec3 _Pos, Vec3 _Scale, Vec3 _Rot, Vec4 _Color, float _Life, bool _DepthTest);
void DrawDebugRect(const Matrix& _matWorld, Vec4 _Color, float _Life, bool _DepthTest);

void DrawDebugCircle(Vec3 _Pos, float _Radius, Vec4 _Color, float _Life, bool _DepthTest);
//void DrawDebugLine();

void DrawDebugCube(Vec3 _Pos, Vec3 _Scale, Vec3 _Rot, Vec4 _Color, float _Life, bool _DepthTest);
void DrawDebugCube(const Matrix& _matWorld, Vec4 _Color, float _Life, bool _DepthTest);

void DrawDebugSphere(Vec3 _Pos, float _Radius, Vec4 _Color, float _Life, bool _DepthTest);
void DrawDebugSphere(const Matrix& _matWorld, Vec4 _Color, float _Life, bool _DepthTest);


string ToString(const wstring& _str);
wstring ToWString(const string& _str);

void SaveWString(const wstring& _String, FILE* _File);
void LoadWString(wstring& _String, FILE* _File);


template<typename T, int _Size>
void Delete_Array(T(&_arr)[_Size])
{
	for (int i = 0; i < _Size; ++i)
	{
		if (nullptr != _arr[i])
			delete _arr[i];
	}
}


template<typename T>
void Delete_Vec(vector<T*>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
			delete _vec[i];
	}
	_vec.clear();
}


template<typename T1, typename T2>
void Delete_Map(map<T1, T2>& _map)
{
	for (const auto& pair : _map)
	{
		if (nullptr != pair.second)
			delete pair.second;
	}
	_map.clear();
}


#include "assets.h"
template<typename T>
ASSET_TYPE GetAssetType()
{
	if constexpr (std::is_same_v<T, qMesh>)
		return ASSET_TYPE::MESH;
	//if constexpr (std::is_same_v<T, qMeshData>)
	//	return ASSET_TYPE::MESH_DATA;
	if constexpr (std::is_same_v<T, qMaterial>)
		return ASSET_TYPE::MATERIAL;
	if constexpr (std::is_same_v<T, qPrefab>)
		return ASSET_TYPE::PREFAB;
	if constexpr (std::is_same_v<T, qTexture>)
		return ASSET_TYPE::TEXTURE;
	if constexpr (std::is_same_v<T, qSound>)
		return ASSET_TYPE::SOUND;
	if constexpr (std::is_same_v<T, qGraphicShader>)
		return ASSET_TYPE::GRAPHIC_SHADER;
	if constexpr (std::is_same_v<T, qComputeShader>)
		return ASSET_TYPE::COMPUTE_SHADER;
	if constexpr (std::is_same_v<T, qSprite>)
		return ASSET_TYPE::SPRITE;
	if constexpr (std::is_same_v<T, qFlipBook>)
		return ASSET_TYPE::FLIPBOOK;
}


#include "qAssetMgr.h"
// File 에 Asset 참조정보 저장 불러오기
template<typename T>
void SaveAssetRef(Ptr<T> Asset, FILE* _File)
{
	bool bAsset = Asset.Get();
	fwrite(&bAsset, 1, 1, _File);

	if (bAsset)
	{
		SaveWString(Asset->GetKey(), _File);
		SaveWString(Asset->GetRelativePath(), _File);
	}
}

template<typename T>
void LoadAssetRef(Ptr<T>& Asset, FILE* _File)
{
	bool bAsset = false;
	fread(&bAsset, 1, 1, _File);

	if (bAsset)
	{
		wstring key, relativepath;
		LoadWString(key, _File);
		LoadWString(relativepath, _File);

		Asset = qAssetMgr::GetInst()->Load<T>(key, relativepath);
	}
}