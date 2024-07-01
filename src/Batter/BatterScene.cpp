#include "Batter/BatterScene.hpp"
#include "SceneManager.hpp"
#include "DrawTextureTiled.hpp"

BatterScene::BatterScene() {
    name = "Batter";
    float beatmap_offset = beatmap.GetMetronomeOffset();
    metronome.SetOffset(beatmap_offset);
    clock.SetOffset(beatmap_offset);
    starBeat = beatmap_offset;
    conductor.Start();
}

BatterScene::~BatterScene() {
    UnloadSound(se_bad);
    UnloadSound(se_good);
    UnloadSound(se_perfect);
    UnloadTexture(stars);
    UnloadTexture(house);
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

    clock.Update();
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
            score -= 1;
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

void BatterScene::ScrollStars() {
    int SCALE = 2;

    // if (conductor.GetSongTimePosition() > starBeat) {
    //     starBeat += conductor.GetCrotchet();
    //     star_scroll_offset.x += 5;
    //     star_scroll_offset.y -= 5;
    // }

    star_scroll_offset.x--;
    if (star_scroll_offset.x <= -stars.width * SCALE)
        star_scroll_offset.x = 0;

    star_scroll_offset.y--;
    if (star_scroll_offset.y <= -stars.height * SCALE)
        star_scroll_offset.y = 0;

    /* Draw star background and loop */
    Rectangle dest = {0,0, 800, 600};
    DrawTextureTiled(stars, dest, star_scroll_offset, SCALE);
}

void BatterScene::Draw() {
    ClearBackground({0x0, 0x0, 0x73, 0xff});

    // Scroll stars infinitely
    ScrollStars();

    // Draw House background
    DrawTexturePro(house,
        {0, 0, 400, 300}, // Source
        {0, 0, 800, 600}, // Dest
        {0, 0},           // Origin
        0,                // Rotation
        WHITE
    );

    inputdisplay.Draw();
    
    if (should_display_score) {
        DisplayScore();
        return;
    }

    char _score[16];
    sprintf(_score, "SCORE: %d", (int)score);
    DrawText(_score, 800/2 - 32, 16, 16, WHITE);

    // beatmap.Draw();
    clock.Draw();
    batter.Draw();
    baseball.Draw();
}


