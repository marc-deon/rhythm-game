#include <stdio.h>
#include <raylib.h>
#include "StreamConductor.hpp"
#include "Metronome.hpp"
#include "CrosshairMetronome.hpp"
#include "BeatmapWithVisualizer.hpp"
#include "Batter/Batter.hpp"
#include "Batter/Baseball.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

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
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "maqo's rhythm game");
    InitAudio();
    SetTargetFPS(60);

    #ifdef LEAKTEST
    leaktest();
    return 0;
    #endif

    SceneManager::ReplaceScene(SCENE_MAINMENU);

    while (!WindowShouldClose()) {
        SceneManager::CheckToReplace();
        
        if (SceneManager::GetCurrent() == NULL) {
            printf("Game exited due to no current scene\n");
            break;
        }
        SceneManager::GetCurrent()->Update();
        BeginDrawing();
        DrawFPS(0, 0);
        SceneManager::GetCurrent()->Draw();
        EndDrawing();
    }
    CloseWindow();
}
