#include <Windows.h>

LRESULT CALLBACK MainWndProc(
    HWND hwnd,        // handle to window
    UINT uMsg,        // message identifier
    WPARAM wParam,    // first message parameter
    LPARAM lParam)    // second message parameter
{

    switch (uMsg)
    {
        case WM_CREATE:
            // Initialize the window.
            return 0;

        case WM_PAINT:
            // Paint the window's client area.
            return 0;

        case WM_SIZE:
            // Set the size and position of the window.
            return 0;

        case WM_DESTROY:
            // Clean up window-specific data objects.
            return 0;

        //
        // Process other messages.
        //

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wndcls{};
    wndcls.cbSize = sizeof(WNDCLASSEX);
    wndcls.style = CS_SAVEBITS | CS_DROPSHADOW;
    wndcls.lpfnWndProc = MainWndProc;
    wndcls.hInstance = hInstance;
    wndcls.lpszClassName = "Viper3";
    RegisterClassEx(&wndcls);

    HWND H = CreateWindowEx(0,
            wndcls.lpszClassName,
            "你是谁",
            0,
            100,100,200,200,
            NULL,NULL,
            hInstance,
            NULL);

    ShowWindow(H, SW_NORMAL);

    MSG msg;
    GetMessage(&msg,H,WM_KEYFIRST,WM_KEYLAST);
    BOOL bRet;
    while( (bRet = GetMessage( &msg, H, 0, 0 )) != 0)
    {
        if (bRet == -1)
        {
            // handle the error and possibly exit
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}
