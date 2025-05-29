#include "raylib.h"
#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

////////////////////////////////////////////////////////////////////////////////////////////
/// Simple Button Function
/// Returns true if clicked, false if not clicked.
bool sBtn(const char* text, Rectangle btn, int fontSize, Color foreColor, Color backColor)
{
    int txtWidth = MeasureText(text, fontSize);
    int marginX = (int)(btn.width - txtWidth) / 2;
    int marginY = (int)(btn.height - fontSize) / 2;
    int border_t = marginY / 2 < 1 ? 1 : marginY / 2;
    Rectangle borderRect = { btn.x + border_t, btn.y + border_t, btn.width - border_t * 2, btn.height - border_t * 2 };
    bool hovered = CheckCollisionPointRec(GetMousePosition(), btn);
    // draw button
    DrawRectangleRounded(btn, 0.5f, 2, hovered ? GOLD : backColor);
    DrawRectangleRoundedLinesEx(borderRect, 0.5f, 2, (float)border_t + 1, hovered ? GRAY : LIGHTGRAY);
    DrawText(text, (int)btn.x + marginX, (int)btn.y + marginY, fontSize, hovered ? WHITE : foreColor);

    return hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}
////////////////////////////////////////////////////////////////////////////////////////////


// polygon pattern
int n = 4;          // regular n-gon
float r = 100.0f;   // Radius of a regular polygon
float a = 0.0f;     // Slope angle of a regular polygon
int v = 40;         // Rotational velocity of a regular polygon
float d = 1.0f;     // Ratio of distance between polygons

// Update and draw in one frame
void UpdateDrawFrame(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    // Draw background patterns
    for (int i = 0; i < 600 + r; i += (int)(r * d)) for (int j = 0; j < 800 + r; j += (int)(r * d))
        DrawPolyLinesEx({ (float)j,(float)i }, n, r, a, 8, PURPLE);

    DrawText("Click the button to change the pattern.", 100, 10, 30, BLACK);

    // Button layout and behavior
    if (sBtn("Polygon",         { 470, 100, 300, 60 }, 40, RAYWHITE, { 130,130,130,180 }))
        n = n < 6 ? n + 1 : 3;
    if (sBtn("Polygon size",    { 470, 200, 300, 60 }, 32, RAYWHITE, { 130,130,130,180 }))
        r = r < 120 ? r + 30 : 60;
    if (sBtn("Polygon Spacing", { 470, 300, 300, 60 }, 30, RAYWHITE, { 130,130,130,180 }))
        d = d < 1.6f ? d + 0.2f : 0.8f;
    if (sBtn("Rotation On/Off", { 470, 520, 300, 60 }, 30, RAYWHITE, { 130,130,130,180 }))
        v = v < 30 ? 30 : 0;
    // angle update
    a = a < 360 ? a + v * GetFrameTime() : 0.0f;

    EndDrawing();
}

// Main
int main(void)
{
    InitWindow(800, 600, "Simple Button Function");

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