#include "../Public/FoxEngine.h"
#include <sstream>
#include <iostream>


namespace FoxEngine
{
    FxEngine::FxEngine() : mbEnginePaused(false), mbEngineMinimized(false),
        mbEngineMaximized(true), mbEngineResizing(false)
    {

    }

    FxEngine::~FxEngine()
        = default;

    int FxEngine::Run()
    {
        while (IsRunning())
        {
            if (!BroadcastMessage()) continue;

            mGameTimer.Tick();
            if (!mbEnginePaused)
            {
                CalculateFrameStats();
                UpdateScene(mGameTimer.DeltaTime());
                DrawScene();
            }
            else
            {
                Sleep(100);
            }
        }
        std::cout << "Exited GameEngine!" << std::endl;
        return 0;
    }

    bool FxEngine::Init()
    {
        if (!InitEngine()) return false;
        if (!InitRenderer()) return false;
        return true;
    }

    FxGraphicsRenderer* FxEngine::GetGraphicsRenderer() const
    {
        if (mpGraphicsRenderer == nullptr) return nullptr;
        return mpGraphicsRenderer;
    }

    void FxEngine::EventOnCreate()
    {
        FxWindow::EventOnCreate();
    }

    void FxEngine::EventOnUpdate()
    {
        FxWindow::EventOnUpdate();
    }

    void FxEngine::EventOnDestroy()
    {
        FxWindow::EventOnDestroy();

        SetThreadPriority(mpThread, THREAD_PRIORITY_IDLE);
        SetPriorityClass(mpProcess, IDLE_PRIORITY_CLASS);
    }

    void FxEngine::EventOnPaused()
    {
        FxWindow::EventOnPaused();
        mbEnginePaused = true;
        mGameTimer.Stop();
    }

    void FxEngine::EventOnResume()
    {
        FxWindow::EventOnResume();
        mbEnginePaused = false;
        mGameTimer.Start();
    }

    void FxEngine::EventOnEnterSizeMove()
    {
        FxWindow::EventOnEnterSizeMove();
        mbEnginePaused = true;
        mbEngineResizing = true;
        mGameTimer.Stop();
        OnResizeBegin();
    }

    void FxEngine::EventOnExitSizeMove()
    {
        FxWindow::EventOnExitSizeMove();
        mbEnginePaused = false;
        mbEngineResizing = false;
        mGameTimer.Start();
        OnResizeEnd();
    }

    bool FxEngine::InitEngine()
    {
        mbEnginePaused = false;
        mbEngineMinimized = false;
        mbEngineMaximized = true;
        mbEngineResizing = false;

        // Optimising thread and process
        constexpr auto processorInfinity = 2;
        mpThread = GetCurrentThread();
        mpProcess = GetCurrentProcess();

        // Set thread and process priorities to very high
        if (!SetThreadPriority(mpThread, THREAD_PRIORITY_TIME_CRITICAL)) {
            SetThreadPriority(mpThread, THREAD_PRIORITY_HIGHEST);
        }
        if (!SetPriorityClass(mpProcess, REALTIME_PRIORITY_CLASS)) {
            SetPriorityClass(mpProcess, HIGH_PRIORITY_CLASS);
        }
        SetProcessAffinityMask(mpProcess, processorInfinity);
        SetThreadAffinityMask(mpThread, processorInfinity);

        return FxWindow::Init();
    }

    bool FxEngine::InitRenderer()
    {
        mpGraphicsRenderer = FxGraphicsRenderer::Get();
        if (mpGraphicsRenderer == nullptr) return false;
        if (mpGraphicsRenderer->InitDevices(GetWindowHandle()) == false) return false;
        return true;
    }

    void FxEngine::CalculateFrameStats() const
    {
        static int frameCounter = 0;
        static float timeElapsed = 0;
        frameCounter++;

        if (mGameTimer.TotalTime() - timeElapsed >= 1.f) {
            const auto fps = static_cast<float>(frameCounter);
            const float mspf = 1000.f / fps;

            std::wostringstream outs;
            outs.precision(6);
            outs << GetWindowName() << L" FPS: " << fps << L" " << mspf << L" (ms)";

            SetWindowTextW(GetWindowHandle(), outs.str().c_str());

            // Reset
            frameCounter = 0;
            timeElapsed += 1.f;
        }
    }
}
