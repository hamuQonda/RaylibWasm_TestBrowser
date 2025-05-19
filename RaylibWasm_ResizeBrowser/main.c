#include "raylib.h"
#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

int screenWidth = 800;
int screenHeight = 600;

void UpdateDrawFrame(void)
{
    BeginDrawing();
    ClearBackground(GRAY);
    int posX = (screenWidth - MeasureText("Resize the browser window", 40)) / 2;
    DrawText("Resize the browser window", posX, 200, 40, GOLD);
    DrawRectangleLinesEx((Rectangle) { 5, 5, screenWidth - 10, screenHeight - 10 }, 10.0f, MAROON);
    EndDrawing();
}

int main(void)
{
    InitWindow(screenWidth, screenHeight, "raylib + WASM Resizable Canvas");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(30);
    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }
#endif

    CloseWindow();

    return 0;
}