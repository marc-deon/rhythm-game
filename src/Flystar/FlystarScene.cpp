#include "Flystar/FlystarScene.hpp"
#include "SceneManager.hpp"

FlystarScene::FlystarScene() {
    name = "Flystar";
    float beatmap_offset = beatmap.GetMetronomeOffset();
    metronome.SetOffset(beatmap_offset);
    conductor.Start();
}

FlystarScene::~FlystarScene() {
    UnloadSound(se_bad);
    UnloadSound(se_good);
    UnloadSound(se_perfect);
}

void FlystarScene::CheckAndScore(KeyboardKey key, int subtype) {
if (IsKeyPressed(key)) {

        int result = beatmap.CheckInRange(subtype);
        if (result == HIT_PERFECT) {
            score += 2;
            PlaySound(se_perfect);
        }

        else if (result == HIT_GOOD) {
            perfect = false;
            score += 1;
            PlaySound(se_good);
        }

        else if (result == HIT_BAD){
            perfect = false;
            score -= 1;
            PlaySound(se_bad);
        }
    }
}

void FlystarScene::Update() {
    if (should_display_score) {
        // Show screen for at least a second
        misc_timer += GetFrameTime();
        if (misc_timer < 1)
            return;

        if (IsKeyPressed(KEY_Z)) {
            SceneManager::ReplaceScene(SCENE_MAINMENU);
            return;
        }
        return;
    }

    conductor.Update();
    metronome.Update();
    auto cue = beatmap.Update();
    if (cue.main == SONG_END || !conductor.IsPlaying()) {
        should_display_score = true;
        misc_timer = 0;
        return;
    }

    CheckAndScore(KEY_Z, junna);
    CheckAndScore(KEY_X, nana);
    
    bool result = beatmap.CheckForMiss();
    if (result) {
        score -= 1;
        PlaySound(se_bad);
    }

    if (IsKeyPressed(KEY_END)) {
        SceneManager::ReplaceScene(SCENE_MAINMENU);
        return;
    }
}

void FlystarScene::DisplayScore() {
    int x, y;    // Location of various texts
    char rating[16]; // perfect string SUPERB!
    if (score / maxScore > score_threshhold_great)
        sprintf(rating, "GREAT!");
    else if (score / maxScore > score_threshhold_ok)
        sprintf(rating, "OK.");
    else 
        sprintf(rating, "AWFUL...");

    // Center horizontally
    x = 800/2 - MeasureText("YOU DID...", 36)/2;
    // Place a fifth down the screen
    y = 600/5 - 36/2;
    // Draw text, with about 12 pixels between each line
    DrawText("YOU DID...", x, y, 36, WHITE);
    if(misc_timer > 1)
        DrawText(rating, x, y+=48, 24, WHITE);

    // Get the starting point
    x = 800 - 20 - MeasureText("PRESS Z TO CONTINUE", 16);
    y = 600 - 20 - 16;
    // Draw partial text                        Update horizontal
    DrawText("PRESS ", x, y, 16, WHITE);        x += MeasureText("PRESS ", 16);
    DrawText("Z", x, y, 16, GREEN);             x += MeasureText("Z", 16);
    DrawText(" TO CONTINUE", x, y, 16, WHITE);
}

void FlystarScene::Draw() {
    ClearBackground(BLACK);

    inputdisplay.Draw();
    beatmap.Draw();
    
    if (should_display_score) {
        DisplayScore();
        return;
    }

    char _score[16];
    sprintf(_score, "SCORE: %d", (int)score);
    DrawText(_score, 800/2 - 32, 16, 16, WHITE);


}


