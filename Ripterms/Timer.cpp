#include "Ripterms.h"

Ripterms::Timer::Timer(std::chrono::milliseconds everyXms)
{
	setEvery(everyXms);
}

bool Ripterms::Timer::isElapsed()
{
	std::chrono::steady_clock::time_point timerNow = std::chrono::steady_clock::now();
	if (duration_cast<std::chrono::milliseconds>(timerNow - timerBegin) >= targetMs) {
		timerBegin = timerNow;
		return true;
	}
	return false;
}

void Ripterms::Timer::setEvery(std::chrono::milliseconds everyXms)
{
	timerBegin = std::chrono::steady_clock::now();
	targetMs = everyXms;
}