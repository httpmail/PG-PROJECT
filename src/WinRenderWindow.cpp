
#include "WinRenderWindow.h"
#include "PGUtil.h"

#include <assert.h>

PG::WinRenderWindow* PG::WinRenderWindow::spInstance = nullptr;

PG::WinRenderWindow::WinRenderWindow()
{
}

PG::WinRenderWindow::~WinRenderWindow()
{
}

bool PG::WinRenderWindow::Create(uint32_t w, uint32_t h, bool bFullScreen /* =false */, const std::wstring & name /* = L"PG Win" */)
{
    assert(!spInstance);

    m_bfullscreen = bFullScreen;
    m_appName     = name;

    WNDCLASSEX wc;
    m_hInstance = GetModuleHandle(NULL);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = m_hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hIconSm = wc.hIcon;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = m_appName.c_str();
    wc.cbSize = sizeof(WNDCLASSEX);

    RegisterClassEx(&wc);


    INT screenWidth = GetSystemMetrics(SM_CXSCREEN);
    INT screenHeight = GetSystemMetrics(SM_CYSCREEN);
    DWORD style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP;
    if (bFullScreen)
    {
        // If full screen set the screen to maximum size of the users desktop and 32bit.
        DEVMODE dmScreenSettings;
        memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
        dmScreenSettings.dmSize = sizeof(dmScreenSettings);
        dmScreenSettings.dmPelsWidth = static_cast<INT>(screenWidth);
        dmScreenSettings.dmPelsHeight = static_cast<INT>(screenHeight);
        dmScreenSettings.dmBitsPerPel = 32;
        dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
        ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
    }
    else
    {
        RECT rect = { 0, 0, static_cast<LONG>(w), static_cast<LONG>(h)};

        style = WS_OVERLAPPEDWINDOW;

        if (!AdjustWindowRect(&rect, style, FALSE))
            return false;

        screenHeight = rect.bottom - rect.top;
        screenWidth = rect.right - rect.left;
    }

    wchar_t tmp[256];
    swprintf_s(tmp, 256, L"%lld", std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
    m_className = m_appName + tmp;

    m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_className.c_str(), m_appName.c_str(),
        style,
        0, 0, screenWidth, screenHeight, NULL, NULL, m_hInstance, NULL);

    ShowWindow(m_hwnd, SW_SHOW);
    SetForegroundWindow(m_hwnd);
    SetFocus(m_hwnd);

    return true;
}

bool PG::WinRenderWindow::SetFullScreen(uint32_t w, uint32_t h, bool bFullScreen)
{
    return false;
}

bool PG::WinRenderWindow::ReSize(uint32_t w, uint32_t h)
{
    return false;
}

void PG::WinRenderWindow::SetPositio(int left, int top)
{
}

LRESULT PG::WinRenderWindow::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT PG::WinRenderWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    assert(spInstance);

    return spInstance->MessageHandler(hWnd, msg, wParam, lParam);
}
