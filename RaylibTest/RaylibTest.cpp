#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <raylib.h>
#include <vector>
#include <String>
#include "raymath.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

using namespace std;

struct CircleButton {
    Vector2 position;
    float radius, maxRadius;
    Color color;
};

struct Timer {
    float currentTime = 0.0f, interval;
    
    Timer(float targetInterval) {
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
};

struct SquareButton {
    Vector2 position, size;
    Color color;
};

struct Item {
    string name;
    int count = 0;
    double cpsPerItem = 0.1;
    double baseCost = 10.0;
    double currentCost = 10.0;
    double costMultiplier = 1.15;

    Item(string n, double cps, double cost) {
        name = n;
        cpsPerItem = cps;
        baseCost = cost;
        currentCost = cost;
    }

    double GetContribuition() {
        return (double)count * cpsPerItem;
    }

    void Buy(double& playerCur) {
        if (playerCur >= currentCost) {
            playerCur -= currentCost;
            count++;
            currentCost *= costMultiplier;

        }
    }
};

typedef enum TextAlignment {
    ALIGN_LEFT      = 0,
    ALIGN_TOP       = 0,
    ALIGN_CENTER    = 1,
    ALIGN_MIDDLE    = 1,
    ALIGN_RIGHT     = 2,
    ALIGN_BOTTOM    = 2
} TextAlignment;

void DrawTextInRect(Font font, const char* text, Rectangle container, int fontSize, int fontSpacing, Color color, TextAlignment hAlign, TextAlignment vAlign)
{
    // 1. Medir o tamanho do texto
    Vector2 textSize = MeasureTextEx(font, text, (float)fontSize, (float)fontSpacing);

    // 2. Calcular a Posição X (Horizontal)
    // A lógica 'Lerp' do exemplo é a mais elegante para isso.
    // (hAlign * 0.5f) converte 0, 1, 2 para 0.0, 0.5, 1.0
    float posX = container.x + Lerp(0.0f, container.width - textSize.x, (float)hAlign * 0.5f);

    // 3. Calcular a Posição Y (Vertical)
    float posY = container.y + Lerp(0.0f, container.height - textSize.y, (float)vAlign * 0.5f);

    // 4. Desenhar o texto na posição calculada
    DrawTextEx(font, text, { posX, posY }, (float)fontSize, (float)fontSpacing, color);
}

typedef enum GameScreen { LOGO = 0, MENU, GAMEPLAY, SHOP } GameScreen;

Color darkPurple = Color{ 34, 24, 40, 16 };

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    // Create
    InitWindow(screenWidth, screenHeight, "Caio Clicker - V.0.0.0.1");
    SetTargetFPS(60);

    // Definindo a tela inicial do jogo
    // GameScreen currentScreen = LOGO; << Pular a splash screen por enquanto
    GameScreen currentScreen = GAMEPLAY;

    // Moeda
    double caios = 0;
    double totalCPS = 0.0;

    // Itens
    vector<Item> itens;
    itens.push_back(Item("Professora de Química", 0.1, 10));
    itens.push_back(Item("Beijo do bubulane", 0.3, 30));
    itens.push_back(Item("Cama de casal", 0.5, 50));
    itens.push_back(Item("Pão", 1, 100));

    // Botao do caio
    CircleButton button;
    button.position = { screenWidth / 2 , screenHeight / 2 };
    button.maxRadius = 60.f;
    button.radius = 50.f;
    button.color = RED;

    // Botao da loja
    Rectangle back = { 10, 10, 50, 50 };

    // Timers

    // UI
    float uiX = 450.f, uiY = 10.f, buttonWidth = 300.f, buttonHeight = 50.f, buttonSpacing = 2.f;

    // Textos
    Font font = LoadFontEx("m5x7.ttf", 72, 0, 250);
    SetTextureFilter(font.texture, TEXTURE_FILTER_POINT);
    int fontSpacing = 1;
    GuiSetFont(font);
    
    // Checagem da fonte
    {
        if (font.texture.id == 0)
        {
            TraceLog(LOG_WARNING, "Fonte não encontrada. Usando fonte padrão.");
        }
        else
        {
            TraceLog(LOG_INFO, "Fonte carregada com sucesso!");
        }
    }

    // Alignment
    const char* textAlignNameH[] = { "Left", "Center", "Right" };
    const char* textAlignNameV[] = { "Top", "Middle", "Bottom" };

    TextAlignment hAlign = ALIGN_CENTER;
    TextAlignment vAlign = ALIGN_MIDDLE;

    // Variáveis gerais
    Vector2 MousePos = { 0 };
    int frameCounter = 0;
    
    // GameLoop
    while (WindowShouldClose() == false) {
        MousePos = GetMousePosition();
        
        // Cálculo dos caios
        totalCPS = 0;
        for (int i = 0; i < itens.size(); i++)
        {   
            totalCPS += itens[i].GetContribuition();
        }
        caios += totalCPS * GetFrameTime();

        // TROCA DAS TELAS
        switch (currentScreen) {
            case GAMEPLAY:
            {
                if (CheckCollisionPointCircle(MousePos, button.position, button.radius)) {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        button.radius += 10;
                        caios += 1;
                    }
                }

                if (button.radius > 50) {
                    button.radius--;
                }
                if (button.radius > button.maxRadius) {
                    button.radius = button.maxRadius;
                }
            } break;
        }

        // Render
        BeginDrawing();
            // Padrões do texto
            GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
            GuiSetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL, TEXT_ALIGN_MIDDLE);
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
            GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt(LIGHTGRAY));
            GuiSetStyle(DEFAULT, TEXT_COLOR_PRESSED, ColorToInt(DARKGRAY));

            switch (currentScreen) {
            case LOGO:
            {
                frameCounter++;
                if (frameCounter > 120) {
                    currentScreen = MENU;
                }
                ClearBackground(BLACK);
                // SplashScreen
                {
                    GuiSetStyle(DEFAULT, TEXT_SIZE, 36);
                    GuiLabel({ 0,0,screenWidth, screenHeight }, "GAME BY SAMTLOKOMEMO");
                }
                
            } break;
            case MENU:
            {
                ClearBackground(DARKGREEN);

                // Título
                {
                    GuiSetStyle(DEFAULT, TEXT_SIZE, 48);
                    GuiLabel({ 0, 0, (float)screenWidth, 100 }, "CAIO CLICKER");
                }

                // Botão jogar
                {
                    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
                    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(RED));
                    float tamanhoDoTexto = MeasureText("JOGAR", 24);
                    if (GuiButton({ screenWidth / 2 - 60, screenHeight / 4, tamanhoDoTexto + 30, 36}, "JOGAR")) currentScreen = GAMEPLAY;
                }
            } break;
            case GAMEPLAY:
            {
                ClearBackground(darkPurple);

                // Título 
                {
                    GuiSetStyle(DEFAULT, TEXT_SIZE, 48);
                    GuiLabel({ 0, 0, (float)screenWidth, 100 }, "CAIO CLICKER");
                }
                // Botão da loja
                {
                    GuiSetStyle(DEFAULT, TEXT_SIZE, 36);
                    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(LIME));
                    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(GREEN));
                    GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, ColorToInt(DARKGREEN));
                    if(GuiButton({ screenWidth - 75, screenHeight - 75, 50.f, 50.f }, "$")) currentScreen = SHOP;
                }
                   
                // Botão do caio
                DrawCircle(button.position.x, button.position.y, button.radius, button.color);
            } break;
            case SHOP:
            {
                ClearBackground(darkPurple);

                // Botão de voltar
                {
                    GuiSetStyle(DEFAULT, TEXT_SIZE, 36);
                    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
                    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(DARKGRAY));
                    GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, ColorToInt(DARKPURPLE));
                    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(LIGHTGRAY));
                    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(GRAY));
                    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(DARKGRAY));
                    if(GuiButton({ 10, 10, 30, 30 }, "<")) currentScreen = GAMEPLAY;
                }
                
                // Título da loja
                {
                    GuiSetStyle(DEFAULT, TEXT_SIZE, 48);
                    GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
                    GuiSetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL, TEXT_ALIGN_TOP);
                    GuiLabel({ 100, 20, (float)screenWidth, (float)screenHeight }, "LOJA\n\n\n DO\n\n\nCAIO");
                }
                
                // Botões dos itens
                {
                    GuiSetStyle(DEFAULT, TEXT_SIZE, 12);
                    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(LIME));
                    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(GREEN));
                    GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, ColorToInt(DARKGREEN));
                    GuiSetStyle(BUTTON, TEXT_COLOR_DISABLED, ColorToInt(RED));
                    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(GREEN));
                    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(DARKGREEN));
                    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt({0 , 120, 100, 255}));
                    GuiSetStyle(BUTTON, BASE_COLOR_DISABLED, ColorToInt({ 114, 47, 55, 255 }));

                    for (int i = 0; i < itens.size(); i++)
                    {
                        Item& item = itens[i];
                        // Criando o botão dinamicamente de acordo com o número de itens
                        float buttonY = uiY + (i * (buttonHeight * buttonSpacing));
                        Rectangle buttonRect = { uiX, buttonY, buttonWidth, buttonHeight };

                        if (caios < item.currentCost)
                        {
                            GuiDisable();
                        }

                        const char* buttonText = TextFormat("%s (%d) | Custo: %.0f",
                            item.name.c_str(),
                            item.count,
                            item.currentCost);

                        // Comprando o item
                        if (GuiButton(buttonRect, buttonText)) item.Buy(caios);
                        GuiEnable();
                    }
                }
            } break;
            }

            // Textos dos valores
            {
                GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
                GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
                GuiSetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL, TEXT_ALIGN_MIDDLE);
                GuiLabel({ 0, screenHeight - 100, (float)screenWidth, 20 }, TextFormat("você tem %.0f caios", caios));
                GuiLabel({ 0, screenHeight - 100, (float)screenWidth, 45 }, TextFormat("você ganha %.1f  caios por segundo", totalCPS));
            }
        EndDrawing();
    }
    UnloadFont(font);
    CloseWindow();
    return 0;
}


