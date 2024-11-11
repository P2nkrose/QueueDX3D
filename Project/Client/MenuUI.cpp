#include "pch.h"
#include "MenuUI.h"

#include <Engine/qPathMgr.h>
#include <Engine/qLevelMgr.h>
#include <Engine/qLevel.h>
#include <Engine/qAssetMgr.h>
#include <Engine/assets.h>
#include <Scripts/qScriptMgr.h>
#include <Engine/qGameObject.h>
#include <Engine/qScript.h>

#include <Engine/qRenderMgr.h>

#include "qEditorMgr.h"
#include "Inspector.h"
#include "qLevelSaveLoad.h"


MenuUI::MenuUI()
{
}

MenuUI::~MenuUI()
{
}

void MenuUI::Tick()
{
	if (!IsActive())
		return;

	if (ImGui::BeginMainMenuBar())
	{
		Update();

		ImGui::EndMainMenuBar();
	}
}

void MenuUI::Update()
{
	File();

	Level();

	GameObject();

	Assets();

	Editor();

	RenderTarget();
}

void MenuUI::File()
{
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Level Save"))
		{
			WCHAR szSelect[256] = {};

			OPENFILENAME filename = {};

			filename.lStructSize = sizeof(filename);
			filename.hwndOwner = nullptr;
			filename.lpstrFile = szSelect;
			filename.lpstrFile[0] = '\0';
			filename.nMaxFile = sizeof(szSelect);
			filename.lpstrFilter = L"ALL\0*.*\0Level\0*.lv";
			filename.nFilterIndex = 1;
			filename.lpstrFileTitle = NULL;
			filename.nMaxFileTitle = 0;

			// 탐색창 초기 위치 지정
			wstring strInitPath = qPathMgr::GetInst()->GetContentPath();
			strInitPath += L"level\\";
			filename.lpstrInitialDir = strInitPath.c_str();

			filename.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetSaveFileName(&filename))
			{
				qLevelSaveLoad::SaveLevel(qPathMgr::GetAbsolutePath(szSelect), qLevelMgr::GetInst()->GetCurrentLevel());
			}
		}

		if (ImGui::MenuItem("Level Load"))
		{
			wchar_t szSelect[256] = {};

			OPENFILENAME filename = {};

			filename.lStructSize = sizeof(filename);
			filename.hwndOwner = nullptr;
			filename.lpstrFile = szSelect;
			filename.lpstrFile[0] = '\0';
			filename.nMaxFile = sizeof(szSelect);
			filename.lpstrFilter = L"ALL\0*.*\0Level\0*.lv";
			filename.nFilterIndex = 1;
			filename.lpstrFileTitle = NULL;
			filename.nMaxFileTitle = 0;

			// 탐색창 초기 위치 지정
			wstring strInitPath = qPathMgr::GetInst()->GetContentPath();
			strInitPath += L"level\\";
			filename.lpstrInitialDir = strInitPath.c_str();

			filename.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetOpenFileName(&filename))
			{
				qLevel* pLevel = qLevelSaveLoad::LoadLevel(qPathMgr::GetAbsolutePath(szSelect));
				ChangeLevel(pLevel, LEVEL_STATE::STOP);

				// Inspector 의 타겟정보를 nullptr 로 되돌리기
				Inspector* pInspector = (Inspector*)qEditorMgr::GetInst()->FindEditorUI("Inspector");
				pInspector->SetTargetObject(nullptr);
			}
		}

		ImGui::EndMenu();
	}
}

void MenuUI::Level()
{

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	ImGui::BeginDisabled(!pCurLevel);

	if (ImGui::BeginMenu("Level"))
	{
		LEVEL_STATE State = LEVEL_STATE::STOP;
		if (nullptr != pCurLevel)
			State = pCurLevel->GetState();

		ImGui::BeginDisabled(LEVEL_STATE::PLAY == State);
		if (ImGui::MenuItem("Play"))
		{
			if (LEVEL_STATE::STOP == State)
			{
				wstring strLevelPath = qPathMgr::GetInst()->GetContentPath();
				strLevelPath += L"level\\Temp.lv";
				qLevelSaveLoad::SaveLevel(strLevelPath, pCurLevel);
			}
			
			ChangeLevelState(LEVEL_STATE::PLAY);
		}
		ImGui::EndDisabled();

		ImGui::BeginDisabled(LEVEL_STATE::PLAY != State);
		if (ImGui::MenuItem("Pause"))
		{
			ChangeLevelState(LEVEL_STATE::PAUSE);
		}
		ImGui::EndDisabled();

		ImGui::BeginDisabled(LEVEL_STATE::STOP == State);
		if (ImGui::MenuItem("Stop"))
		{
			wstring StrLevelLoadPath = qPathMgr::GetInst()->GetContentPath();
			StrLevelLoadPath += L"level\\Temp.lv";
			qLevel* pLoadedLevel = qLevelSaveLoad::LoadLevel(StrLevelLoadPath);
			ChangeLevel(pLoadedLevel, LEVEL_STATE::STOP);

			// Inspector Clear 하기 (이전 오브젝트 정보를 보여주고 있을 수가 있기 때문에)				
			Inspector* pInspector = (Inspector*)qEditorMgr::GetInst()->FindEditorUI("Inspector");
			pInspector->SetTargetObject(nullptr);
			pInspector->SetTargetAsset(nullptr);
		}
		ImGui::EndDisabled();

		ImGui::EndMenu();
	}
	ImGui::EndDisabled();
}

void MenuUI::GameObject()
{
	if (ImGui::BeginMenu("GameObject"))
	{
		if (ImGui::MenuItem("Create Empty Object"))
		{

		}

		if (ImGui::BeginMenu("Add Component"))
		{
			ImGui::MenuItem("MeshRender");
			ImGui::MenuItem("Collider2D");
			ImGui::MenuItem("camera");

			ImGui::EndMenu();
		}

		AddScript();

		ImGui::EndMenu();
	}
}


void MenuUI::AddScript()
{
	if (ImGui::BeginMenu("Add Script"))
	{
		vector<wstring> vecScriptsName;
		qScriptMgr::GetScriptInfo(vecScriptsName);

		for (size_t i = 0; i < vecScriptsName.size(); ++i)
		{
			if (ImGui::MenuItem(string(vecScriptsName[i].begin(), vecScriptsName[i].end()).c_str()))
			{
				qScript* pScript = qScriptMgr::GetScript(vecScriptsName[i]);

				// 인스펙터
				Inspector* pInspector = (Inspector*)qEditorMgr::GetInst()->FindEditorUI("Inspector");

				// 타겟 오브젝트 알아냄
				qGameObject* pObject = pInspector->GetTargetObject();

				if (nullptr != pObject)
				{
					// 오브젝트에, 선택한 스크립트를 추가해줌
					qScript* pScript = qScriptMgr::GetScript(vecScriptsName[i]);
					pObject->AddComponent(pScript);
				}

			}
		}

		ImGui::EndMenu();
	}
}


void MenuUI::Assets()
{
	if (ImGui::BeginMenu("Assets"))
	{
		// Defaul Material 만들기
		if (ImGui::MenuItem("Create Empty Material"))
		{
			Ptr<qMaterial> pMtrl = new qMaterial;
			wstring Key = GetAssetKey(ASSET_TYPE::MATERIAL, L"Default Material");
			qAssetMgr::GetInst()->AddAsset<qMaterial>(Key, pMtrl);
			pMtrl->Save(Key);
		}

		//// Sprite Editor 켜고 끄기
		//EditorUI* pSpriteEditor = qEditorMgr::GetInst()->FindEditorUI("SpriteEditor");
		//bool IsActive = pSpriteEditor->IsActive();

		//if (ImGui::MenuItem("Sprite Editor", nullptr, &IsActive))
		//{
		//	qEditorMgr::GetInst()->FindEditorUI("SpriteEditor")->SetActive(IsActive);
		//}


		//// Default FlipBook 만들기
		//if (ImGui::MenuItem("Create Empty FlipBook"))
		//{
		//	Ptr<qFlipBook> pFlipBook = new qFlipBook;
		//	wstring Key = GetAssetKey(ASSET_TYPE::FLIPBOOK, L"Default FlipBook");
		//	qAssetMgr::GetInst()->AddAsset<qFlipBook>(Key, pFlipBook);
		//}


		ImGui::EndMenu();
	}
}

void MenuUI::Editor()
{
	if (ImGui::BeginMenu("Editor"))
	{

		// Sprite Editor 켜고 끄기
		EditorUI* pSpriteEditor = qEditorMgr::GetInst()->FindEditorUI("SpriteEditor");
		bool IsActive_SE = pSpriteEditor->IsActive();

		if (ImGui::MenuItem("Sprite Editor", nullptr, &IsActive_SE))
		{
			pSpriteEditor->SetActive(IsActive_SE);
		}

		// Animation Editor 켜고 끄기
		EditorUI* pAnimationEditor = qEditorMgr::GetInst()->FindEditorUI("AnimationEditor");
		bool IsActive_AE = pAnimationEditor->IsActive();

		if (ImGui::MenuItem("Animation Editor", nullptr, &IsActive_AE))
		{
			pAnimationEditor->SetActive(IsActive_AE);
		}



		ImGui::EndMenu();
	}
}

void MenuUI::RenderTarget()
{
	if (ImGui::BeginMenu("RenderTarget"))
	{
		Ptr<qTexture> pTarget = qRenderMgr::GetInst()->GetSpecifiedTarget();

		bool IsAlbedo = pTarget == qAssetMgr::GetInst()->FindAsset<qTexture>(L"AlbedoTargetTex");
		bool IsNormal = pTarget == qAssetMgr::GetInst()->FindAsset<qTexture>(L"NormalTargetTex");
		bool IsPosition = pTarget == qAssetMgr::GetInst()->FindAsset<qTexture>(L"PositionTargetTex");
		bool IsEmissive = pTarget == qAssetMgr::GetInst()->FindAsset<qTexture>(L"EmissiveTargetTex");
		bool IsDiffuse = pTarget == qAssetMgr::GetInst()->FindAsset<qTexture>(L"DiffuseTargetTex");
		bool IsSpecular = pTarget == qAssetMgr::GetInst()->FindAsset<qTexture>(L"SpecularTargetTex");

		if (ImGui::MenuItem("Albedo Target", nullptr, &IsAlbedo))
		{
			if (!IsAlbedo)
				qRenderMgr::GetInst()->SetSpecifiedTarget(nullptr);
			else
				qRenderMgr::GetInst()->SetSpecifiedTarget(qAssetMgr::GetInst()->FindAsset<qTexture>(L"AlbedoTargetTex"));
		}

		if (ImGui::MenuItem("Normal Target", nullptr, &IsNormal))
		{
			if (!IsNormal)
				qRenderMgr::GetInst()->SetSpecifiedTarget(nullptr);
			else
				qRenderMgr::GetInst()->SetSpecifiedTarget(
					qAssetMgr::GetInst()->FindAsset<qTexture>(L"NormalTargetTex")
				);
		}

		if (ImGui::MenuItem("Position Target", nullptr, &IsPosition))
		{
			if (!IsPosition)
				qRenderMgr::GetInst()->SetSpecifiedTarget(nullptr);
			else
				qRenderMgr::GetInst()->SetSpecifiedTarget(
					qAssetMgr::GetInst()->FindAsset<qTexture>(L"PositionTargetTex")
				);
		}

		if (ImGui::MenuItem("Emissive Target", nullptr, &IsEmissive))
		{
			if (!IsEmissive)
				qRenderMgr::GetInst()->SetSpecifiedTarget(nullptr);
			else
				qRenderMgr::GetInst()->SetSpecifiedTarget(
					qAssetMgr::GetInst()->FindAsset<qTexture>(L"EmissiveTargetTex")
				);
		}

		if (ImGui::MenuItem("Diffuse Target", nullptr, &IsDiffuse))
		{
			if (!IsDiffuse)
				qRenderMgr::GetInst()->SetSpecifiedTarget(nullptr);
			else
				qRenderMgr::GetInst()->SetSpecifiedTarget(
					qAssetMgr::GetInst()->FindAsset<qTexture>(L"DiffuseTargetTex")
				);
		}

		if (ImGui::MenuItem("Specular Target", nullptr, &IsSpecular))
		{
			if (!IsSpecular)
				qRenderMgr::GetInst()->SetSpecifiedTarget(nullptr);
			else
				qRenderMgr::GetInst()->SetSpecifiedTarget(
					qAssetMgr::GetInst()->FindAsset<qTexture>(L"SpecularTargetTex")
				);
		}

		ImGui::EndMenu();
	}
}


wstring MenuUI::GetAssetKey(ASSET_TYPE _Type, const wstring& _Format)
{
	wstring Key;

	switch (_Type)
	{
	case ASSET_TYPE::MATERIAL:
	{
		Key = wstring(L"material\\") + _Format + L" %d.mtrl";
	}
		break;
	case ASSET_TYPE::PREFAB:
	{
		Key = wstring(L"prefab\\") + _Format + L" %d.pref";
	}
		break;
	case ASSET_TYPE::SPRITE:
	{
		Key = wstring(L"sprite\\") + _Format + L" %d.sprite";
	}
		break;
	case ASSET_TYPE::FLIPBOOK:
	{
		Key = wstring(L"flipbook\\") + _Format + L" %d.flip";
	}
		break;
	default:
		assert(nullptr);
		break;
	}

	wchar_t szKey[255] = {};
	wstring FilePath = qPathMgr::GetInst()->GetContentPath();

	for (UINT i = 0; i < 0xffffffff; ++i)
	{
		swprintf_s(szKey, 255, Key.c_str(), i);

		if (false == std::filesystem::exists(FilePath + szKey))
		{
			break;
		}
	}

	return szKey;
}
