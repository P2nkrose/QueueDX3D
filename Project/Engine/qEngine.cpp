#include "pch.h"
#include "qEngine.h"

#include "qDevice.h"
#include "qPathMgr.h"
#include "qKeyMgr.h"
#include "qTimeMgr.h"
#include "qAssetMgr.h"
#include "qLevelMgr.h"
#include "qRenderMgr.h"
#include "qCollisionMgr.h"
#include "qTaskMgr.h"
#include "qFontMgr.h"
#include "qPrefab.h"


qEngine::qEngine()
	: m_hWnd(nullptr)
	, m_ptResolution{}
{
}

qEngine::~qEngine()
{
	if (nullptr != m_FMODSystem)
	{
		m_FMODSystem->release();
		m_FMODSystem = nullptr;
	}
}

int qEngine::Init(HWND _wnd, POINT _ptResolution, OBJECT_SAVE _SaveFunc, OBJECT_LOAD _Func)
{
	m_hWnd = _wnd;
	m_ptResolution = _ptResolution;
	ChangeWindowScale(_ptResolution.x, _ptResolution.y);

	if (FAILED(qDevice::GetInst()->Init(m_hWnd, m_ptResolution.x, m_ptResolution.y)))
	{
		MessageBox(nullptr, L"장치 초기화 실패", L"CDevice 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// FMOD 초기화		
	FMOD::System_Create(&m_FMODSystem);
	assert(m_FMODSystem);

	// 32개 채널 생성
	m_FMODSystem->init(32, FMOD_DEFAULT, nullptr);



	// Manager 초기화
	qPathMgr::GetInst()->Init();
	qKeyMgr::GetInst()->Init();
	qTimeMgr::GetInst()->Init();
	qAssetMgr::GetInst()->Init();
	qRenderMgr::GetInst()->Init();
	qLevelMgr::GetInst()->Init();
	qFontMgr::GetInst()->Init();

	// Prefab Function 등록
	qPrefab::g_ObjectSaveFunc = _SaveFunc;
	qPrefab::g_ObjectLoadFunc = _Func;


	return S_OK;
}



void qEngine::Progress()
{
	// FMOD Tick
	m_FMODSystem->update();


	// Manager
	qKeyMgr::GetInst()->Tick();
	qTimeMgr::GetInst()->Tick();
	qAssetMgr::GetInst()->Tick();
	qLevelMgr::GetInst()->Progress();

	// Collision
	qCollisionMgr::GetInst()->Tick();
	
	// Render
	qRenderMgr::GetInst()->Tick();



	// Task Manager
	qTaskMgr::GetInst()->Tick();
}


void qEngine::ChangeWindowScale(UINT _Width, UINT _Height)
{
	bool bMenu = false;
	if (GetMenu(m_hWnd))
		bMenu = true;

	RECT rt = { 0, 0, _Width, _Height };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, bMenu);
	SetWindowPos(m_hWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
}