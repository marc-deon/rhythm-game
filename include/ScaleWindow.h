
#define VIRT_SCREEN_W 800
#define VIRT_SCREEN_H 600
#define MIN(a, b) (b < a ? b : a)

float FindWindowScale() {
    // Use whichever is smaller between the width's and height's scales
    float w = (float)GetScreenWidth()/VIRT_SCREEN_W;
    float h = (float)GetScreenHeight()/VIRT_SCREEN_H;
    return MIN(w, h);
}

Vector2 ScaleMouse(float scale) {
    // Update virtual mouse (clamped mouse value behind game screen)
    Vector2 mouse = GetMousePosition();
    Vector2 virtualMouse = {
        .x = (mouse.x - (GetScreenWidth() - (VIRT_SCREEN_W*scale))*0.5f)/scale,
        .y = (mouse.y - (GetScreenHeight() - (VIRT_SCREEN_H*scale))*0.5f)/scale
    };
    
    virtualMouse = Vector2Clamp(virtualMouse, {0, 0}, { VIRT_SCREEN_W, VIRT_SCREEN_H });

    // Apply the same transformation as the virtual mouse to the real mouse (i.e. to work with raygui)
    SetMouseOffset(-(GetScreenWidth() - (VIRT_SCREEN_W*scale))*0.5f, -(GetScreenHeight() - (VIRT_SCREEN_H*scale))*0.5f);
    SetMouseScale(1/scale, 1/scale);
    return virtualMouse;
}

void DrawScaled(RenderTexture2D target, float scale) {
    BeginDrawing();

    // Clear window background w/ black bars
    ClearBackground(BLACK);

    // Draw render texture to screen, properly scaled
    DrawTexturePro(target.texture, (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
                    (Rectangle){ (GetScreenWidth() - ((float)VIRT_SCREEN_W*scale))*0.5f, (GetScreenHeight() - ((float)VIRT_SCREEN_H*scale))*0.5f,
                    (float)VIRT_SCREEN_W*scale, (float)VIRT_SCREEN_H*scale }, (Vector2){ 0, 0 }, 0.0f, WHITE);
    EndDrawing();
}