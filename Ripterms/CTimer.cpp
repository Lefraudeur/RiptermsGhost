#include "Ripterms.h"

Ripterms::CTimer::CTimer(std::chrono::milliseconds everyXms)
    : timerBegin(std::chrono::steady_clock::now()), targetMs(everyXms)
{
}

bool Ripterms::CTimer::isElapsed()
{
    auto timerNow = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(timerNow - timerBegin) >= targetMs)
    {
        timerBegin = timerNow;
        return true;
    }
    return false;
}

void Ripterms::CTimer::setEvery(std::chrono::milliseconds everyXms)
{
    targetMs = everyXms;
    reset();
}

void Ripterms::CTimer::reset()
{
    timerBegin = std::chrono::steady_clock::now();
}
