#pragma once
#include "Raylib.h"

struct Timer {
    float currentTime;
    float interval;

    // Construtor
    Timer(float targetInterval);

    bool Tick();
    void Reset();
};

