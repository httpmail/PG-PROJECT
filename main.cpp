
#include "WinRenderWindow.h"
#include "PGUtil.h"

class ABCxxx : PG::WinRenderWindow {
public:
    ABCxxx() {}
    ~ABCxxx() {}

public:
    virtual bool Create(uint32_t w, uint32_t h, bool bFullScreen = false, const std::wstring& name = L"PG Win")
    {
        return PG::WinRenderWindow::Create(w, h);
    }

protected:
    virtual LRESULT CALLBACK MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        return PG::WinRenderWindow::MessageHandler(hWnd, msg, wParam, lParam);
    }
};

#include <assert.h>
#include <iostream>

int main()
{
}