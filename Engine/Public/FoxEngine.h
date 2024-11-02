#pragma once

#include "Window.h"
#include "GameTimer.h"
#include "GraphicsRenderer.h"


namespace FoxEngine
{
    class FxEngine : public FxWindow
    {
        //~ Components
        FxGameTimer mGameTimer;
        FxGraphicsRenderer* mpGraphicsRenderer{};

        //~ Booleans
        bool mbEnginePaused;
        bool mbEngineMinimized;
        bool mbEngineMaximized;
        bool mbEngineResizing;

        //~ Config
        void* mpThread { nullptr };
        void* mpProcess{ nullptr };
    public:
        FxEngine();
        ~FxEngine() override;

        int Run();
        bool Init() override;
        
        [[nodiscard]] 
        FxGraphicsRenderer* GetGraphicsRenderer() const;

        void EventOnCreate() override;
        void EventOnUpdate() override;
        void EventOnDestroy() override;

        void EventOnPaused() override;
        void EventOnResume() override;

        void EventOnEnterSizeMove() override;
        void EventOnExitSizeMove() override;

    protected:
        bool InitEngine();
        bool InitRenderer();

        void CalculateFrameStats() const;
    };
}
