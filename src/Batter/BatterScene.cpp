#include "Batter/BatterScene.hpp"
#include "SceneManager.hpp"

BatterScene::BatterScene() {
    name = "Batter";
    metronome.SetOffset(beatmap.GetMetronomeOffset());
    conductor.Start();
}

BatterScene::~BatterScene() {
    UnloadSound(se_bad);
    UnloadSound(se_good);
    UnloadSound(se_perfect);
}

void BatterScene::Update() {
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

    batter.Update();
    baseball.Update(cue);
    if (IsKeyPressed(KEY_Z)) {
        batter.Swing();

        int result = beatmap.CheckInRange();
        if (result == HIT_PERFECT) {
            score += 2;
            PlaySound(se_perfect);
            baseball.PlayPerfect();
        }

        else if (result == HIT_GOOD) {
            perfect = false;
            score += 1;
            PlaySound(se_good);
            baseball.PlayGood();
        }

        else if (result == HIT_BAD){
            perfect = false;
            PlaySound(se_bad);
            baseball.PlayBad();
        }
    }

    if (IsKeyPressed(KEY_END)) {
        SceneManager::ReplaceScene(SCENE_MAINMENU);
        return;
    }
}

void BatterScene::DisplayScore() {
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

void BatterScene::Draw() {
    ClearBackground(BLACK);
    
    if (should_display_score) {
        DisplayScore();
        return;
    }
    // beatmap.Draw();
    batter.Draw();
    baseball.Draw();
}


