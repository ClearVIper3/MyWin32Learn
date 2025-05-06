#define UNICODE
#define _UNICODE
#include <Windows.h>
#include <windowsx.h>

#define BTN_BTN_1 1000
#define BTN_CHECKBOX_1 2000
#define BTN_RADIO_1 3000
#define ID_EDITCHILD 100

static HWND hwndEdit;
    TCHAR lpszLatin[] =  L"Lorem ipsum dolor sit amet, consectetur "
                         L"adipisicing elit, sed do eiusmod tempor "
                         L"incididunt ut labore et dolore magna "
                         L"aliqua. Ut enim ad minim veniam, quis "
                         L"nostrud exercitation ullamco laboris nisi "
                         L"ut aliquip ex ea commodo consequat. Duis "
                         L"aute irure dolor in reprehenderit in "
                         L"voluptate velit esse cillum dolore eu "
                         L"fugiat nulla pariatur. Excepteur sint "
                         L"occaecat cupidatat non proident, sunt "
                         L"in culpa qui officia deserunt mollit "
                         L"anim id est laborum.";

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        hwndEdit = CreateWindowEx(
            0, L"EDIT", NULL,
            WS_CHILD | WS_VISIBLE | WS_VSCROLL |
            ES_LEFT | ES_MULTILINE | WS_BORDER,
            150, 150, 200, 200,
            hwnd,
            (HMENU)ID_EDITCHILD,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL);

        SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)lpszLatin);
        return 0;

    case WM_COMMAND:
        if (LOWORD(wParam) == BTN_BTN_1) {
            TCHAR lpszLatin1[500]{};
            Edit_GetText(hwndEdit, lpszLatin1,500);
            MessageBox(hwnd, lpszLatin1, L"提示", MB_OK);
        } else if (LOWORD(wParam) == BTN_CHECKBOX_1) {
            MessageBox(hwnd, L"checkbox 按钮被按下", L"提示", MB_OK);
        } else if (LOWORD(wParam) == BTN_RADIO_1) {
            MessageBox(hwnd, L"radio 按钮被按下", L"提示", MB_OK);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wndcls{};
    wndcls.cbSize = sizeof(WNDCLASSEX);
    wndcls.lpfnWndProc = MainWndProc;
    wndcls.hInstance = hInstance;
    wndcls.lpszClassName = L"Viper3";
    RegisterClassEx(&wndcls);

    HWND m_hwnd = CreateWindowEx(0,
        wndcls.lpszClassName,
        L"你是谁",
        WS_OVERLAPPEDWINDOW,
        100, 100, 600, 800,
        NULL, NULL,
        hInstance, NULL);

    CreateWindow(L"BUTTON", L"OK",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        10, 10, 100, 50,
        m_hwnd, (HMENU)BTN_BTN_1,
        hInstance, NULL);

    CreateWindow(L"BUTTON", L"CHECKBOX",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
        150, 10, 100, 50,
        m_hwnd, (HMENU)BTN_CHECKBOX_1,
        hInstance, NULL);

    CreateWindow(L"BUTTON", L"RADIO",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
        10, 150, 100, 50,
        m_hwnd, (HMENU)BTN_RADIO_1,
        hInstance, NULL);

    ShowWindow(m_hwnd, nCmdShow);
    UpdateWindow(m_hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
