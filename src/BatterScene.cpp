#include "BatterScene.hpp"
#include "SceneManager.hpp"

BatterScene::BatterScene() {
    name = "Batter";
    conductor.Start();
}

void BatterScene::Exit() { } 

void BatterScene::Update() {
    conductor.Update();
    metronome.Update();
    auto cue = beatmap.Update();
    batter.Update();
    baseball.Update(cue);
    if (IsKeyPressed(KEY_Z)) {
        batter.Swing();

        int result = beatmap.CheckInRange();
        if (result == HIT_PERFECT) {
            PlaySound(se_perfect);
            baseball.PlayPerfect();
        }

        else if (result == HIT_GOOD) {
            PlaySound(se_good);
            baseball.PlayGood();
        }

        else if (result == HIT_BAD){
            PlaySound(se_bad);
            baseball.PlayBad();
        }
    }

    if (IsKeyPressed(KEY_END)) {
        SceneManager::ReplaceScene(SCENE_MAINMENU);
        return;
    }
}

void BatterScene::Draw() {
    ClearBackground(BLACK);
    // beatmap.Draw();
    batter.Draw();
    baseball.Draw();
}


