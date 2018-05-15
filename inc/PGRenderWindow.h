#pragma once

#include <string>

namespace PG {
    class RenderWindow {
    public:
        RenderWindow() {}
        virtual ~RenderWindow() {}

    public:
        virtual bool Create(uint32_t w, uint32_t h, bool bFullScreen, const std::wstring& name) = 0;
        virtual bool SetFullScreen(uint32_t w, uint32_t h, bool bFullScreen) = 0;
        virtual bool ReSize(uint32_t w, uint32_t h) = 0;
        virtual void SetPositio(int left, int top) = 0;

    private:
        RenderWindow(const RenderWindow&) = delete;
        RenderWindow& operator=(const RenderWindow&) = delete;
    };
}
