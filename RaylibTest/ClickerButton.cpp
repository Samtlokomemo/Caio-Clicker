#include "ClickerButton.h"
ClickerButton::ClickerButton(Vector2 pos, float startRadius, float maxRad, Color c) {
	position = pos;
	radius = startRadius;
	maxRadius = maxRad;
	color = c;
	growRate = 10.0f;
	shrinkRate = 60.0f;
}

bool ClickerButton::Update(Vector2 mousePos) {
	if (CheckCollisionPointCircle(mousePos, position, radius)) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			radius += growRate;
			return true;
		}
	}

	if (radius > 50.0f) { // 50.0f é o tamanho base, pode parametrizar se quiser
		radius -= shrinkRate * GetFrameTime();

		// Impede que fique menor que o mínimo
		if (radius < 50.0f) radius = 50.0f;
	}

	// 3. Limite de Tamanho
	if (radius > maxRadius) radius = maxRadius;

	return false;
}

void ClickerButton::Draw() {
	DrawCircle(position.x, position.y, radius, color);
}