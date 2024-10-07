#pragma once

#include "EditorUI.h"

class ParamUI
{
public:
	// Scalar Parameter
	static bool InputInt(int* _Data, const string& _Desc);
	static bool DragInt(int* _Data, float _Step, const string& _Desc);

	static bool InputFloat(float* _Data, const string& _Desc);
	static bool DragFloat(float* _Data, float _Step, const string& _Desc);

	static bool InputVec2(Vec2* _Data, const string& _Desc);
	static bool DragVec2(Vec2* _Data, float _Step, const string& _Desc);

	static bool InputVec4(Vec4* _Data, const string& _Desc);
	static bool DragVec4(Vec4* _Data, float _Step, const string& _Desc);


public:
	// Texture Parameter
	static bool InputTexture(Ptr<qTexture>& _CurTex, const string& _Desc, EditorUI* _Inst = nullptr, DELEGATE_1 _MemFunc = nullptr);

public:
	// Prefab Parameter
	static bool InputPrefab(Ptr<qPrefab>& _CurPrefab, const string& _Desc, EditorUI* _Inst = nullptr, DELEGATE_1 _MemFunc = nullptr);


public:
	static void ResetID() { g_ID = 0; }


private:
	static UINT g_ID;
};

