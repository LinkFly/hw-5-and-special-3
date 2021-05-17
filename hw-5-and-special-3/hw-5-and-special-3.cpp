// hw-5-and-special-3.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "hw-5-and-special-3.h"
#include "home-work-5.h"

#include <string>
#include <sstream>

using std::wstring;
using std::wstringstream;
using std::to_wstring;
using std::stoi;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
HWND hMainWnd;                                      // current window
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND defaultButton; // Activate on start

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HW5ANDSPECIAL3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // Default activate (run Task1)
    MSG msgClick;
    ZeroMemory(&msgClick, sizeof(msgClick));
    msgClick.hwnd = hMainWnd;
    msgClick.message = WM_COMMAND;
    msgClick.lParam = LPARAM(defaultButton);
    DispatchMessage(&msgClick);
    ////

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HW5ANDSPECIAL3));
    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HW5ANDSPECIAL3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HW5ANDSPECIAL3);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   HWND hWnd;
   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   hMainWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //// Data for tasks
    // for task1
    static double arNums[] = { 1.1, 2.2, 3.3, 4.4 };
    // for task2
    static uint8_t arBits[] = { 1, 1, 0, 0, 1, 0, 1, 1, 0, 0 };
    // for task3
    static int arInts[8] = {0};
    // for task4
    static int arTask4[] = { 1, 2, 3, 4, 5 };
    // for task5
    //static int arTask5[] = {1, 1, 1, 2, 1};
    //static int arTask5[] = { 2, 1, 1, 2, 1 };
    static int arTask5[] = {10, 1, 2, 3, 4};
    

    static HWND hBtn, hBtnTask2, hBtnTask3, hBtnTask4, hBtnTask5,
                hTask1Result, hTask2Result, hTask3Result, hTask4Result, hTask5Result;
    static HWND hTask4Rotate, hTask4Edit, hTask5InData;
    static HFONT hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, _T("Consolas"));

    auto fnCreateBtn = [&hWnd](const wchar_t* caption, int x, int y, int width, int height) {
		HWND hNew = CreateWindow(L"button", caption, WS_CHILD | WS_VISIBLE | WS_BORDER,
			x, y, width, height, hWnd, nullptr, hInst, nullptr);
		ShowWindow(hNew, SW_SHOWNORMAL);
        return hNew;
	};

	auto fnCreateEdit = [&hWnd](const wchar_t* caption, int x, int y, int width, int height) {
		HWND hNew = CreateWindow(L"edit", caption, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
			x, y, width, height, hWnd, nullptr, hInst, nullptr);
        SendMessage(hNew, WM_SETFONT, (WPARAM)hFont, NULL);
		ShowWindow(hNew, SW_SHOWNORMAL);
		return hNew;
	};

	auto fnCreateLabel = [&hWnd](const wchar_t* caption, int x, int y, int width, int height) {
		HWND hNew = CreateWindow(L"static", caption, WS_CHILD | WS_VISIBLE,
            x, y, width, height, hWnd, nullptr, hInst, nullptr);
		SendMessage(hNew, WM_SETFONT, (WPARAM)hFont, NULL);
		ShowWindow(hNew, SW_SHOWNORMAL);
        return hNew;
	};

    int curY = 0;
    switch (message)
    {
    case WM_CREATE:
        // task 1
        hBtn = fnCreateBtn(L"Задание 1:", 0, curY, 120, 30);
        defaultButton = hBtn;
        hTask1Result = fnCreateLabel(L"", 120, curY, 400, 30);

        // task 2
        curY += 50;
		hBtnTask2 = fnCreateBtn(L"Задание 2:", 0, curY, 120, 30);
		hTask2Result = fnCreateLabel(L"", 120, curY, 500, 30);

		// task 3
		curY += 50;
		hBtnTask3 = fnCreateBtn(L"Задание 3:", 0, curY, 120, 30);
		hTask3Result = fnCreateLabel(L"", 120, curY, 500, 30);

		// task 4
		curY += 50;
		hBtnTask4 = fnCreateBtn(L"Задание 4:", 0, curY, 120, 30);
        hTask4Rotate = fnCreateLabel(L"Rotate:", 120, curY, 100, 30);
        hTask4Edit = fnCreateEdit(L"", 220, curY, 50, 30);
        SetWindowText(hTask4Edit, L"-1");
		hTask4Result = fnCreateLabel(L"", 300, curY, 400, 30);
        SetOutputWnd(hTask4Result);
        OutputNumsArray(arTask4, sizeof(arTask4) / sizeof(arTask4[0]));

		// task 5
		curY += 50;
		hBtnTask5 = fnCreateBtn(L"Задание 5:", 0, curY, 120, 30);
        hTask5InData = fnCreateLabel(L"", 120, curY, 300, 30);
		SetOutputWnd(hTask5InData);
		OutputNumsArray(arTask5, sizeof(arTask5) / sizeof(arTask5[0]));
		hTask5Result = fnCreateLabel(L"", 420, curY, 500, 30);

		break;
    case WM_COMMAND:
        {
            if (lParam == (LPARAM)hBtn) {
                SetOutputWnd(hTask1Result);
                OutputDoubleArray(arNums, sizeof(arNums) / sizeof(arNums[0]));
                return 0;
            }

			if (lParam == (LPARAM)hBtnTask2) {
				SetOutputWnd(hTask2Result);
				OutputXorArray(arBits, sizeof(arBits) / sizeof(arBits[0]));
				return 0;
			}

			if (lParam == (LPARAM)hBtnTask3) {
				SetOutputWnd(hTask3Result);
                OutputFillArrayByStep3(arInts, sizeof(arInts) / sizeof(arInts[0]));
				return 0;
			}

			if (lParam == (LPARAM)hBtnTask4) {
				SetOutputWnd(hTask4Result);
                constexpr int sRotSize = 10;
                wchar_t lpszRot[sRotSize + 1];
                auto res = GetWindowText(hTask4Edit, lpszRot, sRotSize + 1);
                if (!res) error(L"Failed get rotate value");
                int64_t rotate = std::stoi(wstring{ lpszRot });
                OutputRotateArray(arTask4, rotate);
				return 0;
			}

			if (lParam == (LPARAM)hBtnTask5) {
				SetOutputWnd(hTask5Result);
                OutputIsBalanceArray(arTask5);
				return 0;
			}
            
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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
