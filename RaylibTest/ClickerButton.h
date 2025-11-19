#pragma once
#include "raylib.h"

class ClickerButton
{
public:
    Vector2 position;
    float radius;
    float maxRadius;
    float growRate;
    float shrinkRate;
    Color color;

    ClickerButton(Vector2 pos, float startRadius, float maxRad, Color c);
    
    bool Update(Vector2 mousePos);
    
    void Draw();
};

