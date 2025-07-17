#include <windows.h>
#include "resource.h"

HINSTANCE hInst;
HFONT hFont;
HWND hStatic_Atlas;
HFONT hButtonFont;
HWND hLoginButton;
HWND hSignupButton;
HWND hCatchphrase;
HFONT hCatchphraseFont;

int Scale(int value, int dpi)
{
    return MulDiv(value, dpi, 96);
}

void RepositionControls(HWND hWnd)
{
    RECT rect;
    GetClientRect(hWnd, &rect);
    int windowWidth = rect.right - rect.left;
    int dpi = GetDpiForWindow(hWnd);

    int atlasWidth = Scale(300, dpi);
    int atlasHeight = Scale(60, dpi);
    int atlasX = (windowWidth - atlasWidth) / 2;
    int atlasY = Scale(100, dpi);
    SetWindowPos(hStatic_Atlas, NULL, atlasX, atlasY, atlasWidth, atlasHeight, SWP_NOZORDER);

    int phraseWidth = Scale(400, dpi);
    int phraseHeight = Scale(30, dpi);
    int phraseX = (windowWidth - phraseWidth) / 2;
    int phraseY = Scale(150, dpi);
    SetWindowPos(hCatchphrase, NULL, phraseX, phraseY, phraseWidth, phraseHeight, SWP_NOZORDER);

    int buttonWidth = Scale(120, dpi);
    int buttonHeight = Scale(40, dpi);
    int buttonGap = Scale(10, dpi);
    int groupWidth = (buttonWidth * 2) + buttonGap;

    int loginX = (windowWidth - groupWidth) / 2;
    int signupX = loginX + buttonWidth + buttonGap;
    int buttonY = Scale(200, dpi);

    SetWindowPos(hLoginButton, NULL, loginX, buttonY, buttonWidth, buttonHeight, SWP_NOZORDER);
    SetWindowPos(hSignupButton, NULL, signupX, buttonY, buttonWidth, buttonHeight, SWP_NOZORDER);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    hInst = hInstance;
    int dpi = GetDpiForSystem();

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (CreateSolidBrush(RGB(240, 240, 240)));
    wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MYMENU);
    wcex.lpszClassName = L"AtlasApp";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    HWND hWnd = CreateWindow(L"AtlasApp", L"ATLAS - Preserve the truth.", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, Scale(800, dpi), Scale(600, dpi), NULL, NULL, hInstance, NULL);

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
        int dpi = GetDpiForWindow(hWnd);
        hFont = CreateFont(Scale(48, dpi), 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET,
            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS, L"Segoe UI");

        hButtonFont = CreateFont(Scale(18, dpi), 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET,
            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS, L"Segoe UI");

        hStatic_Atlas = CreateWindow(L"STATIC", L"ATLAS", WS_VISIBLE | WS_CHILD | SS_CENTER,
            0, 0, 0, 0, hWnd, NULL, hInst, NULL);

        hCatchphraseFont = CreateFont(Scale(22, dpi), 0, 0, 0, FW_NORMAL, TRUE, FALSE, FALSE, ANSI_CHARSET,
            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS, L"Segoe UI");

        hCatchphrase = CreateWindow(L"STATIC", L"Preserve the Truth.", WS_VISIBLE | WS_CHILD | SS_CENTER,
            0, 0, 0, 0, hWnd, NULL, hInst, NULL);

        hLoginButton = CreateWindow(L"BUTTON", L"Login", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            0, 0, 0, 0, hWnd, (HMENU)1, hInst, NULL);

        hSignupButton = CreateWindow(L"BUTTON", L"Sign Up", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            0, 0, 0, 0, hWnd, (HMENU)2, hInst, NULL);
        
        if (hFont)
        {
            SendMessage(hStatic_Atlas, WM_SETFONT, (WPARAM)hFont, TRUE);
            SendMessage(hCatchphrase, WM_SETFONT, (WPARAM)hFont, TRUE);
        }

		if (hButtonFont)
        {
            SendMessage(hLoginButton, WM_SETFONT, (WPARAM)hButtonFont, TRUE);
            SendMessage(hSignupButton, WM_SETFONT, (WPARAM)hButtonFont, TRUE);
        }

        if (hCatchphraseFont)
        {
            SendMessage(hCatchphrase, WM_SETFONT, (WPARAM)hCatchphraseFont, TRUE);
        }

        RepositionControls(hWnd);
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
    case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        if ((HWND)lParam == hStatic_Atlas || (HWND)lParam == hCatchphrase)
        {
            SetTextColor(hdcStatic, RGB(70, 107, 159));

            SetBkMode(hdcStatic, TRANSPARENT);

            return (LRESULT)GetStockObject(NULL_BRUSH);
        }
    }
    break;
    case WM_SIZE:
    {
        RepositionControls(hWnd);
    }
	break;
    case WM_DESTROY:
		DeleteObject(hFont);
        DeleteObject(hButtonFont);
		DeleteObject(hCatchphraseFont);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}