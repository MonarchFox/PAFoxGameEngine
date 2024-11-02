#pragma once

#include <windows.h>

namespace FoxEngine
{
    class FxGameTimer
    {
        //~ Members
        double  mSecondsPerCount;
        double  mDeltaTime;
        __int64 mBaseTime;
        __int64 mPauseTime;
        __int64 mStopTime;
        __int64 mPrevTime;
        __int64 mCurrTime;
        bool    bStopped;

    public:
        FxGameTimer();

        [[nodiscard]] float TotalTime() const;
        [[nodiscard]] float DeltaTime() const;

        void Reset();
        void Start();
        void Stop();
        void Tick();
    };
}
