#pragma once

#include "Window.h"
#include "GameTimer.h"
#include "GraphicsRenderer.h"
#include "AssetsManager.h"


#include <memory>
#include <vector>


namespace FoxEngine
{

    class FxEngine : public FxWindow
    {
    public:
        FxEngine();
        ~FxEngine() override;

        int Run();
        bool Init() override;
        
        void RenderScene();

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

    private:
        //~ Builds Assets that are pending for building
        void BuildAssets();

    private:
        //~ Components
        FxAssetsManager mAssetsManager;
        FxGameTimer mGameTimer;
        FxGraphicsRenderer* mpGraphicsRenderer{};

        //~ Booleans
        bool mbEnginePaused;
        bool mbEngineMinimized;
        bool mbEngineMaximized;
        bool mbEngineResizing;

        //~ Config
        void* mpThread{ nullptr };
        void* mpProcess{ nullptr };
    };
}
