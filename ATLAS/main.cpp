#include <windows.h>
#include "resource.h"

HINSTANCE hInst;
HFONT hFont;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    hInst = hInstance;

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MYMENU);
    wcex.lpszClassName = L"AtlasApp";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    HWND hWnd = CreateWindow(L"AtlasApp", L"ATLAS - Preserve the truth.", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        hFont = CreateFont(48, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET,
            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS, L"Segoe UI");

        HWND hStatic = CreateWindow(L"STATIC", L"ATLAS", WS_VISIBLE | WS_CHILD | SS_CENTER,
            250, 100, 300, 60, hWnd, NULL, hInst, NULL);

        if (hFont)
        {
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
        }

        CreateWindow(L"BUTTON", L"Login", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            300, 200, 100, 30, hWnd, (HMENU)1, hInst, NULL);
        CreateWindow(L"BUTTON", L"Sign Up", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            410, 200, 100, 30, hWnd, (HMENU)2, hInst, NULL);
    }
    break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case 1:
            MessageBox(hWnd, L"Login button clicked!", L"Action", MB_OK);
            break;
        case 2:
            MessageBox(hWnd, L"Signup button clicked!", L"Action", MB_OK);
            break;
        case ID_VISION:
            MessageBox(hWnd, L"Vision menu item clicked!", L"Menu", MB_OK);
            break;
        case ID_MISSION:
            MessageBox(hWnd, L"Mission menu item clicked!", L"Menu", MB_OK);
            break;
        case ID_CONTACT:
            MessageBox(hWnd, L"Contact menu item clicked!", L"Menu", MB_OK);
            break;
        }
        break;
    case WM_DESTROY:
		DeleteObject(hFont);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}