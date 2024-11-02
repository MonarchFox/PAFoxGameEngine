#include <Windowsx.h>
#include <iostream>
#include <stdexcept>

#include "Window.h"


namespace FoxEngine
{

#pragma region MainWindow_Constructors
    FxWindow* mFxWindow{ nullptr };

    LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_CREATE:
        {
            return S_OK;
        }
        case WM_SHOWWINDOW:
        {
            if (wParam)  mFxWindow->EventOnCreate();
            return S_OK;
        }
        case WM_PAINT:
        {
            return S_OK;
        }
        case WM_ACTIVATE:
        {
            if (LOWORD(wParam) == WA_INACTIVE) mFxWindow->EventOnPaused();
            else mFxWindow->EventOnResume();
            return S_OK;
        }
        case WM_ENTERSIZEMOVE:
        {
            mFxWindow->EventOnEnterSizeMove();
            return S_OK;
        }
        case WM_EXITSIZEMOVE:
        {
            mFxWindow->EventOnExitSizeMove();
            return S_OK;
        }
        case WM_SIZE:
        {
            return S_OK;
        }
        case WM_DESTROY:
        {
            mFxWindow->EventOnDestroy();
            PostQuitMessage(0);
            return S_OK;
        }
        case WM_MENUCHAR:
        {
            return MAKELRESULT(0, MNC_CLOSE);
        }
        case WM_GETMINMAXINFO:
        {
            reinterpret_cast<MINMAXINFO*>(lParam)->ptMinTrackSize.x = mFxWindow->GetMinWindowWidth();
            reinterpret_cast<MINMAXINFO*>(lParam)->ptMinTrackSize.y = mFxWindow->GetMinWindowHeight();
            return S_OK;
        }
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
        {
            mFxWindow->OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            return S_OK;
        }
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP:
        {
            mFxWindow->OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            return S_OK;
        }
        case WM_MOUSEMOVE:
        {
            mFxWindow->OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            return S_OK;
        }
        default:
            break;
        }
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    bool FxWindow::InitWindow()
    {
        WNDCLASSEX wc{};
        wc.style = CS_HREDRAW | CS_VREDRAW;  // Add redrawing styles
        wc.cbSize = sizeof(wc);
        wc.hbrBackground = reinterpret_cast<HBRUSH>(BLACK_BRUSH);
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
        wc.hInstance = GetModuleHandle(nullptr);
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
        wc.lpfnWndProc = WindowProc;
        wc.lpszClassName = GetWindowName();  // Ensure this is std::wstring
        wc.lpszMenuName = nullptr;  // Set to nullptr if no menu

        if (!RegisterClassEx(&wc)) {
            DWORD error = GetLastError();
            std::cerr << "RegisterClassEx failed with error: " << error << std::endl;
            return false;
        }
        if (!mFxWindow) mFxWindow = this;

        mHandleWindow = CreateWindowEx(
            WS_EX_OVERLAPPEDWINDOW,
            GetWindowName(),
            GetWindowName(),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            GetWindowWidth(), GetWindowHeight(),
            nullptr, nullptr,
            GetModuleHandle(nullptr),
            nullptr
        );

        if (!mHandleWindow) {
            DWORD error = GetLastError();
            std::cerr << "CreateWindowEx failed with error: " << error << std::endl;
            return false;
        }

        ShowWindow(mHandleWindow, SW_SHOW);
        UpdateWindow(mHandleWindow);

        bRunning = true;
        return true;
    }

    FxWindow::~FxWindow()
    {
        DestroyWindow(GetWindowHandle());
    }

#pragma endregion


    bool FxWindow::Init()
    {
        if (!InitWindow()) return false;

        return true;
    }

    bool FxWindow::Release() const
    {
        if (!DestroyWindow(mHandleWindow)) return false;
        return true;
    }

    bool FxWindow::BroadcastMessage()
    {
        MSG msg;
        bool ret = false;
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            ret = true;
        }
        return ret;
    }

    void FxWindow::EventOnDestroy()
    {
        SetRunning(false);
    }

#pragma region Getters
    RECT FxWindow::GetWindowRect() const
    {
        RECT windowSize;
        GetClientRect(mHandleWindow, &windowSize);
        return windowSize;
    }

    HWND FxWindow::GetWindowHandle() const
    {
        return mHandleWindow;
    }

    float FxWindow::GetAspectRatio() const
    {
        return static_cast<float>(mWindowWidth) / static_cast<float>(mWindowHeight);
    }
#pragma endregion

#pragma region Setters
    void FxWindow::SetWindowName(const std::wstring text)
    {
        mWindowName = text;
    }
#pragma endregion



}