#include <stdio.h>
#include <raylib.h>
#include "raymath.h"
#include "SceneManager.hpp"
#include "ScaleWindow.h"

#define VIRT_SCREEN_W 800
#define VIRT_SCREEN_H 600

void InitAudio() {
    InitAudioDevice();
}

// #define LEAKTEST
void leaktest() {
    int i = 0;
    while (true) {
        SceneManager::ReplaceScene((SCENES)i);
        SceneManager::CheckToReplace();
        i++;
        i %= SCENE_MAX_COUNT;
    }
}

int main() {
    SetTraceLogLevel(LOG_DEBUG);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(VIRT_SCREEN_W, VIRT_SCREEN_H, "maqo's rhythm game");
    SetWindowMinSize(320, 240);

    RenderTexture2D target = LoadRenderTexture(VIRT_SCREEN_W, VIRT_SCREEN_H);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

    InitAudio();
    SetTargetFPS(60);

    #ifdef LEAKTEST
    leaktest();
    return 0;
    #endif

    SceneManager::ReplaceScene(SCENE_MAINMENU);

    while (!WindowShouldClose()) {
        float scale = FindWindowScale();
        Vector2 virtualMouse = ScaleMouse(scale);

        SceneManager::CheckToReplace();

        if (SceneManager::GetCurrent() == NULL) {
            printf("Game exited due to no current scene\n");
            break;
        }

        FocusStack::Update();

        SceneManager::GetCurrent()->Update();

        // Draw game to virtual screen texture
        BeginTextureMode(target);
        // DrawFPS(0, 0);
        SceneManager::GetCurrent()->Draw();
        EndTextureMode();

        // Draw virtual screen to real screen
        DrawScaled(target, scale);
    }
    CloseWindow();
}
