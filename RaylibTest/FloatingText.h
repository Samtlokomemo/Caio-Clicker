#pragma once
#include <string>
#include <iostream>
#include "raylib.h"

struct FloatingText {
    Vector2 position;
    float lifetime;
    std::string text;

    FloatingText(Vector2 pos, float life, std::string txt);
};

