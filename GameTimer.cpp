#include "GameTimer.h"

namespace FoxEngine
{
    FxGameTimer::FxGameTimer() :
        mSecondsPerCount(0), mDeltaTime(-1),
        mBaseTime(0), mPauseTime(0), mPrevTime(0),
        mCurrTime(0), bStopped(false), mStopTime(0)
    {
        __int64 countsPerSecond;
        QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&countsPerSecond));
        mSecondsPerCount = 1.0f / static_cast<double>(countsPerSecond);
    }

    float FxGameTimer::TotalTime() const
    {
        if (bStopped)
        {
            const auto atTime = static_cast<double>((mStopTime - mPauseTime) - mBaseTime);
            return static_cast<float>(atTime * mSecondsPerCount);
        }
        const auto atTime = static_cast<double>((mCurrTime - mPauseTime) - mBaseTime);
        return static_cast<float>(atTime * mSecondsPerCount);
    }

    float FxGameTimer::DeltaTime() const
    {
        return static_cast<float>(mDeltaTime);
    }

    void FxGameTimer::Reset()
    {
        __int64 currentTime;
        QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentTime));

        mBaseTime = currentTime;
        mPrevTime = currentTime;
        mStopTime = 0;
        bStopped = false;
    }

    void FxGameTimer::Start()
    {
        __int64 startTime;
        QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&startTime));
        if (bStopped)
        {
            mPauseTime += (startTime - mStopTime);
            mPrevTime = startTime;
            mStopTime = 0;
            bStopped = false;
        }
    }

    void FxGameTimer::Stop()
    {
        if (!bStopped)
        {
            __int64 currTime;
            QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime));
            mStopTime = currTime;
            bStopped = true;
        }
    }

    void FxGameTimer::Tick()
    {
        if (bStopped)
        {
            mDeltaTime = 0.0;
            return;
        }
        __int64 currTime;
        QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime));
        mCurrTime = currTime;
        mDeltaTime = static_cast<double>(mCurrTime - mPrevTime) * mSecondsPerCount;
        mPrevTime = mCurrTime;

        if (mDeltaTime < 0.0) mDeltaTime = 0.0;
    }
}
