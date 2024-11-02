#pragma once

#include <windows.h>
#include <string>


namespace FoxEngine
{
    class FxWindow
    {
        HWND mHandleWindow{};
        std::wstring mWindowName{ L"FoxGameEngine" };
        int mWindowWidth{ 1280 };
        int mWindowHeight{ 720 };
        bool bRunning{ false };

        // Configurations
        int mMinWindowWidth{ 200 };
        int mMinWindowHeight{ 200 };

    public:
        FxWindow() = default;
        virtual ~FxWindow();

        // Framework Methods
        virtual bool Init();
        virtual void OnResizeBegin() {}
        virtual void OnResizeEnd() {}

        virtual void UpdateScene(float deltaTime)   = 0;
        virtual void DrawScene()                    = 0;

        // Input Handling
        virtual void OnMouseDown(WPARAM btnState, int x, int y) {}
        virtual void OnMouseUp(WPARAM btnState, int x, int y) {}
        virtual void OnMouseMove(WPARAM btnState, int x, int y) {}

        bool Release() const;

        // Events Callback
        [[nodiscard("Must be used for handling messages")]]
        virtual bool BroadcastMessage();
        virtual void EventOnCreate() {}
        virtual void EventOnPaused() {}
        virtual void EventOnResume() {}
        virtual void EventOnEnterSizeMove() {}
        virtual void EventOnExitSizeMove() {}
        virtual void EventOnUpdate() {}
        virtual void EventOnDestroy();

        // Public Getters
        [[nodiscard]] bool           IsRunning()       const { return bRunning;             }
        [[nodiscard]] int            GetWindowWidth()  const { return mWindowWidth;         }
        [[nodiscard]] const wchar_t* GetWindowName()   const { return mWindowName.c_str();  }
        [[nodiscard]] int            GetWindowHeight() const { return mWindowHeight;        }

        [[nodiscard]] RECT      GetWindowRect()   const;
        [[nodiscard]] HWND      GetWindowHandle() const;
        [[nodiscard]] float     GetAspectRatio()     const;

        [[nodiscard]] int       GetMinWindowWidth()  const { return mMinWindowWidth; }
        [[nodiscard]] int       GetMinWindowHeight() const { return mMinWindowHeight; }

    protected:
        virtual bool InitWindow();

        // Setters
        void SetWindowName(const std::wstring text);

        void SetWindowWidth(const int width) { mWindowWidth = width; }
        void SetWindowHeight(const int height) { mWindowHeight = height; }
        void SetRunning(const bool running) { bRunning = running; }
        void SetMinWindowWidth(const int minWidth) { mMinWindowWidth = minWidth; }
        void SetMinWindowHeight(const int minHeight) { mMinWindowHeight = minHeight; }
    };
}

