#include "pch.h"
#include "AE_Detail.h"
#include "AE_Preview.h"
#include "AE_SpriteList.h"
#include "qEditorMgr.h"
#include "ListUI.h"
#include "TreeUI.h"

#include <Engine/qAssetMgr.h>
#include <Engine/qTimeMgr.h>


AE_Detail::AE_Detail()
	: m_Mode{0, 0}
	, m_FPS(0)
	, m_Repeat(0)
	, m_CurSpriteIndex(-1)
	, m_CurFlipBookName("")
	, m_MaxSpriteIndex(0)
	, m_IsActive(0)
	, m_Playing(false)
	, m_AccTime(0.f)
	, m_MaxTime(0.f)
{
}

AE_Detail::~AE_Detail()
{
}

void AE_Detail::Init()
{
	m_CurFlipBook = nullptr;
	m_CurSprite = nullptr;
	m_AtlasTex = nullptr;

	m_CurFlipBookName = "";
	m_CurSpriteName = "";
	m_FPS = 0.f;
	m_Offset = Vec2(0, 0);
	m_Repeat = false;
	m_CurSpriteIndex = -1;
	m_MaxSpriteIndex = 0;

	m_Mode[0] = 0;
	m_Mode[1] = 0;
	m_IsActive = false;
}


void AE_Detail::SetFlipBookData()
{
	GetSpriteList()->SetSpriteToList(m_CurFlipBook->GetVecSprite());
	m_CurFlipBookName = string(m_CurFlipBook->GetKey().begin(), m_CurFlipBook->GetKey().end());
	m_CurSprite = m_CurFlipBook->GetSprite(0);
	m_AtlasTex = m_CurSprite->GetAtlasTexture();
	m_FPS = m_CurFlipBook->GetFPS();
	m_Offset = m_CurSprite->GetOffsetUV() * Vec2(m_AtlasTex->Width(), m_AtlasTex->Height());
	m_Background = m_CurSprite->GetBackgroundUV() * Vec2(m_AtlasTex->Width(), m_AtlasTex->Height());
	m_CurSpriteIndex = 0;
	m_MaxSpriteIndex = m_CurFlipBook->GetMaxFrameCount();
}

void AE_Detail::SetSpriteData()
{
	m_CurSprite = GetSpriteList()->GetCurSprite();
	path Path = m_CurSprite->GetKey();
	m_CurSpriteName = Path.stem().string();
	m_AtlasTex = m_CurSprite->GetAtlasTexture();
	m_CurSpriteIndex = GetSpriteList()->GetCurSpriteIndex();
	m_MaxSpriteIndex = GetSpriteList()->GetSpriteCount();
	m_Offset = m_CurSprite->GetOffsetUV() * Vec2(m_AtlasTex->Width(), m_AtlasTex->Height());
	m_Background = m_CurSprite->GetBackgroundUV() * Vec2(m_AtlasTex->Width(), m_AtlasTex->Height());
}


void AE_Detail::Update()
{
	if (m_Mode[0] || m_Mode[1])
		m_IsActive = true;
	else
		m_IsActive = false;

	SelectMode();

	FlipBookInfo();

	FlipBookPlay();

	SpriteInfo();

	if (m_Mode[0] || m_Mode[1])
		SaveFlipBook();

}




void AE_Detail::SelectMode()
{
	ImGui::Text("");

	if (m_Mode[0] || m_Mode[1])
	{
		ImGui::BeginDisabled();
		ImGui::SetCursorPosX((ImGui::GetWindowSize().x * 0.5f) - 105.f);
		ImGui::Button("NEW", ImVec2(100.f, 18.f));
		ImGui::SameLine(0.f, 10.f);
		ImGui::Button("LOAD", ImVec2(100.f, 18.f));
		ImGui::EndDisabled();
	}
	else
	{
		ImGui::SetCursorPosX((ImGui::GetWindowSize().x * 0.5f) - 105.f);
		if (ImGui::Button("NEW", ImVec2(100.f, 22.f)))
		{
			// Create New FlipBook
			m_Mode[0] = true;
			m_CurFlipBook = new qFlipBook;
		}

		ImGui::SameLine(0.f, 10.f);

		if (ImGui::Button("LOAD", ImVec2(100.f, 22.f)))
		{
			m_Mode[1] = true;
			ListUI* pListUI = (ListUI*)qEditorMgr::GetInst()->FindEditorUI("List");
			pListUI->ShowNameOnly(true);
			pListUI->SetName("FlipBook");

			vector<string> vecFlipBookNames;
			qAssetMgr::GetInst()->GetAssetNames(ASSET_TYPE::FLIPBOOK, vecFlipBookNames);
			pListUI->AddList(vecFlipBookNames);
			pListUI->AddDelegate(this, (DELEGATE_1)&AE_Detail::SelectFlipBook);
			pListUI->SetActive(true);
		}
	}

	if (m_Mode[0])
	{
		ImGui::Text("");
		ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "                   Create New FlipBook");
		//ImGui::TextDisabled(" Create New FlipBook");
		ImGui::SameLine(ImGui::GetWindowSize().x - 50.f);
		if (ImGui::Button("EXIT", ImVec2(40.f, 18.f)))
		{
			m_CurFlipBook = nullptr;
			m_Mode[0] = false;
		}
	}
	else if (m_Mode[1])
	{
		ImGui::Text("");
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "                   Selected Edit FlipBook");
		//ImGui::TextDisabled(": Already exists FlipBook Edit Mode");
		ImGui::SameLine(ImGui::GetWindowSize().x - 50.f);
		if (ImGui::Button("EXIT", ImVec2(40.f, 18.f)))
		{
			m_CurFlipBook = nullptr;
			m_Mode[1] = false;
		}
	}
	else
	{
		ImGui::Text("");
	}
}

void AE_Detail::FlipBookPlay()
{
	ImGui::Text("");

	if (!m_IsActive)
		ImGui::BeginDisabled();


	ImGui::SetCursorPosX((ImGui::GetWindowSize().x * 0.5f) - 105.f);
	if (ImGui::Button("PLAY", ImVec2(100.f, 22.f)))
	{
		// Play FlipBook
		m_Playing = true;
		//m_AccTime = 0.f;
	}
	ImGui::SameLine(0.f, 10.f);
	if (ImGui::Button("PAUSE", ImVec2(100.f, 22.f)))
	{
		// Stop FlipBook
		m_Playing = false;
		m_CurSpriteIndex = 0;
		m_AccTime = 0.f;
	}

	if (m_Playing)
	{
		m_AccTime += EngineDT;

		// 시간에 따른 프레임 전환
		if (m_AccTime >= (1.0f / m_FPS))
		{
			m_AccTime -= (1.0f / m_FPS); // 프레임 전환 후 시간 초기화
			m_CurSpriteIndex++;

			if (m_CurSpriteIndex >= m_MaxSpriteIndex)
			{
				if (m_Repeat)
				{
					m_CurSpriteIndex = 0; // 반복이 설정되어 있으면 처음부터 다시
				}
				else
				{
					m_Playing = false; // 반복이 없으면 재생 중지
					m_CurSpriteIndex = m_MaxSpriteIndex - 1; // 마지막 프레임에서 멈춤
				}
			}

			GetSpriteList()->SetCurSpriteIndex(m_CurSpriteIndex);
		}
	}

	if (!m_IsActive)
		ImGui::EndDisabled();
}



void AE_Detail::SelectFlipBook(DWORD_PTR _ListUI)
{
	ListUI* pListUI = (ListUI*)_ListUI;
	string strName = pListUI->GetSelectName();

	if (strName == "None")
	{
		m_Mode[1] = false;
		m_CurFlipBook = nullptr;
		return;
	}

	wstring strAssetName = wstring(strName.begin(), strName.end());
	Ptr<qFlipBook> pFlipBook = qAssetMgr::GetInst()->FindAsset<qFlipBook>(strAssetName);

	assert(pFlipBook.Get());

	m_CurFlipBook = pFlipBook;
	SetFlipBookData();

}


void AE_Detail::FlipBookInfo()
{
	if (m_Mode[0] || m_Mode[1])
	{
		ImGui::Text("");
	}
	else
	{
		ImGui::Text("");
		ImGui::Text("");
	}


	ImGui::SeparatorText("FlipBook Info");

	if (!m_IsActive)
		ImGui::BeginDisabled();

	ImGui::Text("FlipBook Name");
	ImGui::SameLine(120);
	ImGui::SetNextItemWidth(250);

	if (ImGui::InputText("##FlipBookName", m_CurFlipBookName.data(), 255))
	{
		m_CurFlipBookName.resize(strlen(m_CurFlipBookName.c_str()));
	};

	ImGui::Text("");

	// Frame Index
	int frameCount = m_CurSpriteIndex + 1;
	ImGui::Text("Frame Index");
	ImGui::SameLine(120);
	ImGui::SetNextItemWidth(30);
	ImGui::InputInt("##CurFrameCount", &frameCount, 0, 0, ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();
	ImGui::Text("/");
	ImGui::SameLine();
	ImGui::Text(std::to_string(m_MaxSpriteIndex).c_str());
	ImGui::SameLine(0.f, 77.f);

	int leftIndex = m_CurSpriteIndex;
	if (m_MaxSpriteIndex < 1 || leftIndex == 0)
		ImGui::BeginDisabled();
	if (ImGui::ArrowButton("##left", ImGuiDir_Left))
	{
		if (m_CurSpriteIndex > 0)
			m_CurSpriteIndex--;

		GetSpriteList()->SetCurSpriteIndex(m_CurSpriteIndex);
	}
	if (m_MaxSpriteIndex < 1 || leftIndex == 0)
		ImGui::EndDisabled();

	ImGui::SameLine(0.0f, 5.f);

	int index = m_CurSpriteIndex;
	if (index == m_MaxSpriteIndex - 1)
		ImGui::BeginDisabled();
	if (ImGui::ArrowButton("##right", ImGuiDir_Right))
	{
		m_CurSpriteIndex++;
		if (m_MaxSpriteIndex <= m_CurSpriteIndex)
			m_CurSpriteIndex = m_MaxSpriteIndex - 1;

		GetSpriteList()->SetCurSpriteIndex(m_CurSpriteIndex);
	}
	if (index == m_MaxSpriteIndex - 1)
		ImGui::EndDisabled();

	// FPS
	ImGui::Text("FPS");
	ImGui::SameLine(120);
	ImGui::SetNextItemWidth(180);
	ImGui::InputFloat("##FlipBookFPS", &m_FPS);
	if (m_FPS < 0) m_FPS = 0;

	// Repeat
	ImGui::Text("Repeat");
	ImGui::SameLine(120);
	ImGui::Checkbox("##FlipBookRepeat", &m_Repeat);

	ImGui::Text("");

	if (!m_IsActive)
		ImGui::EndDisabled();

}




void AE_Detail::SpriteInfo()
{
	if (m_Mode[0] || m_Mode[1])
	{
		ImGui::Text("");
		ImGui::Text("");
		ImGui::Text("");
	}
	else
	{
		ImGui::Text("");
		ImGui::Text("");
		ImGui::Text("");
		//ImGui::Text("");
	}


	ImGui::SeparatorText("Sprite Info");

	if (!m_IsActive)
		ImGui::BeginDisabled();

	ImGui::Text("Current Sprite");
	ImGui::SameLine(120);
	ImGui::SetNextItemWidth(250);
	ImGui::InputText("##CurSpriteName", (char*)m_CurSpriteName.c_str(), 255);

	ImGui::Text("");

	float size[2] = { 0, 0 };
	if (m_CurSprite != nullptr)
	{
		size[0] = m_CurSprite->GetBackgroundUV().x * m_AtlasTex->Width();
		size[1] = m_CurSprite->GetBackgroundUV().y * m_AtlasTex->Height();
	}
	ImGui::Text("Sprite Size");
	ImGui::SameLine(120);
	ImGui::SetNextItemWidth(180);
	ImGui::InputFloat2("##CurSpriteSize", size, "%.2f");

	float offset[2] = { m_Offset.x, m_Offset.y };
	ImGui::Text("Offset");
	ImGui::SameLine(120);
	ImGui::SetNextItemWidth(180);
	ImGui::DragFloat2("##CurSpriteOffset", offset, 0.1f);

	//m_AtlasTex->SetOffset(Vec2(OffsetUV.x, OffsetUV.y));

	float background[2] = { m_Background.x, m_Background.y };
	ImGui::Text("Background");
	ImGui::SameLine(120);
	ImGui::SetNextItemWidth(180);
	ImGui::InputFloat2("##CurSpriteBackground", background, "%.2f");

	ImGui::Text("");

	if (!m_IsActive)
		ImGui::EndDisabled();
}


void AE_Detail::SaveFlipBook()
{
	ImGui::Text("");
	ImGui::Text("");


	static int clicked = 0;
	ImGui::SetCursorPosX((ImGui::GetWindowSize().x * 0.5f) - 90.f);
	if(ImGui::Button("SAVE FLIPBOOK", ImVec2(200.f, 22.f)))
		clicked++;

	if (0 < clicked)
	{
		clicked = 0;

		m_CurFlipBook->SetFPS(m_FPS);
		for (int i = 0; i < GetSpriteList()->GetSpriteCount(); ++i)
		{
			m_CurFlipBook->AddSprite(GetSpriteList()->m_vecAddedSprite[i]);
		}

		wstring Path = qPathMgr::GetInst()->GetContentPath();
		Path += wstring(L"Animation\\") + wstring(m_CurFlipBookName.begin(), m_CurFlipBookName.end());
		Path += L".flip";
		m_CurFlipBook->Save(Path);

		GetSpriteList()->Init();
		Init();

	}

}