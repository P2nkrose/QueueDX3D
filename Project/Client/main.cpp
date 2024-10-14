#include "pch.h"
#include "framework.h"
#include "Client.h"

#include "qEditorMgr.h"
#include <Engine/qDevice.h>
#include "ImGui/imgui_impl_win32.h"

#include "qLevelSaveLoad.h"
#include "qTestLevel.h"
#include "qLevel_logo.h"
#include "qLevel_loading1.h"
#include "qLevel_title.h"
#include "qLevel_loading.h"
#include "qLevel_stage1.h"
#include "qLevel_stage2.h"
#include "qLevel_boss.h"

// 전역 변수:
HINSTANCE g_hInst = nullptr;


ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{

    // 랜드값 시간으로 주기
    srand((unsigned int)time(nullptr));

    // 메모리 릭 검사
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(318349);



    g_hInst = hInstance;    // 인스턴스 핸들을 전역 변수에 저장합니다.

    MyRegisterClass(hInstance);

    HWND hWnd = CreateWindowW(L"MyWindowClass", L"Queue DirectX 3D", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // qEngine 객체 초기화
    if (FAILED(qEngine::GetInst()->Init(hWnd
                                      , POINT{ 1600, 900 }
                                      , (OBJECT_SAVE)&qLevelSaveLoad::SaveGameObject
                                      , (OBJECT_LOAD)&qLevelSaveLoad::LoadGameObject)))
    {
        MessageBox(nullptr, L"qEngine 초기화 실패", L"엔진 초기화 실패", MB_OK);
        return 0;
    }




#ifdef _DEBUG
   // Editor Manager 초기화
    qEditorMgr::GetInst()->Init();
#endif

    // 테스트용 레벨 초기상태 만들기
    qTestLevel::CreateTestLevel();
    //qLevel_boss::CreateStageBoss();
    //qLevel_stage2::CreateStage2();
    //qLevel_stage1::CreateStage1();
    //qLevel_loading::CreateLoading();
    //qLevel_title::CreateTitle();
    //qLevel_loading1::CreateLoading1();
    //qLevel_logo::CreateLogo();
    
    

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));
    MSG msg = {};

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_QUIT)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            qEngine::GetInst()->Progress();

#ifdef _DEBUG
            qEditorMgr::GetInst()->Tick();
#endif

            qDevice::GetInst()->Present();
        }
        
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;//MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName  = L"MyWindowClass";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_DPICHANGED:
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
        {
            //const int dpi = HIWORD(wParam);
            //printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
            const RECT* suggested_rect = (RECT*)lParam;
            ::SetWindowPos(hWnd, nullptr, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
        }
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
