#include "Timer.h"
float currentTime = 0.0f, interval;

Timer::Timer(float targetInterval) {
    interval = targetInterval;
}

bool Tick() {
    currentTime += GetFrameTime();
    if (currentTime >= interval) {
        currentTime -= interval;
        return true;
    }
    return false;
}

void Reset() {
    currentTime = 0.0f;
}