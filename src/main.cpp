#include <stdio.h>
#include <raylib.h>
#include "StreamConductor.hpp"
#include "Metronome.hpp"
#include "CrosshairMetronome.hpp"
#include "BeatmapWithVisualizer.hpp"
#include "Batter.hpp"
#include "Baseball.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


void InitAudio() {
    InitAudioDevice();
}


int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "maqo's rhythm game");
    InitAudio();
    SetTargetFPS(100);

    SceneManager::ReplaceScene(SCENE_MAINMENU);

    while (!WindowShouldClose()) {
        // SceneManager::ReplaceScene(SCENE_MAINMENU);
        // SceneManager::ReplaceScene(SCENE_METROHOP);
        if (SceneManager::GetCurrent() == NULL) {
            printf("Game exited due to no current scene\n");
            break;
        }
        SceneManager::GetCurrent()->Update();
        BeginDrawing();
        SceneManager::GetCurrent()->Draw();
        EndDrawing();
    }
    CloseWindow();
}
