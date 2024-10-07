#pragma once

#include "ImGui/imgui.h"

class EditorUI
{
public:
	EditorUI();
	virtual ~EditorUI();

public:
	virtual void Init() {}
	virtual void Tick();
	virtual void Update() PURE;			// 자식이 override받아서 쓰는 고유의 Tick

	
public:
	bool IsActive() { return m_Active; }


public:
	void AddChild(EditorUI* _UI);

	EditorUI* GetParent() { return m_Parent; }
	const vector<EditorUI*>& GetChildren() { return m_vecChildren; }

	void SetName(const string& _Name);
	const string& GetName() { return m_Name; }

	UINT GetID() { return m_ID; }
	const string& GetFullName() { return m_FullName; }

	void SetChildBorder(bool _Set) { m_ChildBorder = _Set; }
	void SetChildSize(ImVec2 _Size) { m_ChildSize = _Size; }

	void SetActive(bool _Active);

	void SetModal(bool _Modal) { m_Modal = _Modal; }
	bool IsModal() { return m_Modal; }

	void SetFocus();

	void ShowNameOnly(bool _NameOnly) { m_ShowNameOnly = _NameOnly; }
	bool IsShowNameOnly() { return m_ShowNameOnly; }

	//EditorUI* GetOwner() { return m_Owner; }
	//void SetOwner(EditorUI* _Owner) { m_Owner = _Owner; }

	void UseMenuBar(bool _Use) { m_UseMenuBar = _Use; }
	void SetMove(bool _Move) { m_Move = _Move; }

private:
	virtual void Activate() {}
	virtual void Deactivate() {}


private:
	static UINT			m_GlobalID;

	string				m_Name;
	string				m_FullName;
	const UINT			m_ID;
	bool				m_Active;

	EditorUI*			m_Parent;
	vector<EditorUI*>	m_vecChildren;

	ImVec2				m_ChildSize;

	bool				m_Modal;
	bool				m_ChildBorder;

	bool				m_UseMenuBar;
	bool				m_Move;


	bool				m_ShowNameOnly;

	//class EditorUI*		m_Owner;

};

typedef void(EditorUI::* DELEGATE_0)(void);
typedef void(EditorUI::* DELEGATE_1)(DWORD_PTR);
typedef void(EditorUI::* DELEGATE_2)(DWORD_PTR, DWORD_PTR);
typedef void(EditorUI::* DELEGATE_3)(DWORD_PTR, DWORD_PTR, DWORD_PTR);