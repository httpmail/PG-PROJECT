#pragma once

#include "PGRenderWindow.h"
#include <Windows.h>

namespace PG {
    class WinRenderWindow : RenderWindow{

    public:
        WinRenderWindow();
        virtual ~WinRenderWindow();

        WinRenderWindow(const WinRenderWindow&) = delete;
        WinRenderWindow& operator=(const WinRenderWindow&) = delete;

    public:
        virtual bool Create(uint32_t w, uint32_t h, bool bFullScreen = false, const std::wstring& name = L"PG Win") = 0;
        virtual bool SetFullScreen(uint32_t w, uint32_t h, bool bFullScreen = true);
        virtual bool ReSize(uint32_t w, uint32_t h);
        virtual void SetPositio(int left, int top);

    protected:
        virtual LRESULT CALLBACK MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

    private:
        static  LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    private:
        HWND            m_hwnd;
        HINSTANCE       m_hInstance;
        std::wstring    m_appName;
        std::wstring    m_className;

        bool            m_bfullscreen;
        int32_t         m_left;
        int32_t         m_right;

    private:
        static WinRenderWindow* spInstance;
    };
}