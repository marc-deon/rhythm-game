#include "Metrohop.hpp"
#include "Metronome.hpp"
#include "Metro_Light.hpp"
#include "SceneManager.hpp"

// Use negatives for early
#define HIT_PERFECT 1
#define HIT_GOOD 2
#define HIT_BAD 3


Metrohop::Metrohop() {
    name = "Metrohop";

    conductor.SetBpm(180);

    children.push_back(new Metro_Light(&conductor, GREEN, DARKGREEN, 1));
    children.push_back(new Metro_Light(&conductor, YELLOW, ORANGE, 2));
    children.push_back(new Metro_Light(&conductor, RED, DARKRED, 3));
    children.push_back(new Metronome(&conductor, 3));
}


float Metrohop::GetErrorRange() {
    // Accuracy for player is within +/- an eighth note
    return conductor.GetCrotchet() / 2;
}


int Metrohop::CheckInRange() {
    // Some nonsense to do modulo on float
    float pos = (conductor.GetIntegerBeat() % 3) + conductor.GetFractionalBeat();

    float e = GetErrorRange();

    if (pos <= e/2)
        return HIT_PERFECT;  // Late
    else if (pos >= 3-e/2)
        return -HIT_PERFECT; // Early
    else if (pos <= e)
        return HIT_GOOD;     // Late
    else if (pos >= 3-e)     
        return -HIT_GOOD;    // Early
    else
        return HIT_BAD;
}

void Lose() {
    exit(0);
}

int last_beat_tapped = 0;
void Metrohop::Update(){
    if (IsKeyPressed(KEY_END)) {
        SceneManager::ReplaceScene(SCENE_MAINMENU);
    }

    conductor.Update();
    int int_beat = conductor.GetIntegerBeat();
    float current_beat = conductor.GetSongBeatPosition();
    float e = GetErrorRange();

    if(IsKeyPressed(KEY_Z)) {
        // Double tap
        if (last_beat_tapped == int_beat || last_beat_tapped+1 == int_beat)
            Lose();

        // Check accuracy
        auto attempt = CheckInRange();
        
        if (abs(attempt) == HIT_BAD){
            Lose();
            printf("%f, Bad\n", current_beat);
        }
        else if (abs(attempt) == HIT_GOOD) {
            last_beat_tapped = attempt > 0 ? int_beat : int_beat+1;
            score+=1;
            // TODO: Figure out how to nicely change BPM
            // if (score % 2 == 0)
            //     conductor.SetBpm(conductor.GetBpm()+10);
            printf("%f, Good\n", current_beat);
        }
        else if (abs(attempt) == HIT_PERFECT) {
            last_beat_tapped = attempt > 0 ? int_beat : int_beat+1;
            score+=1;
            // TODO: Figure out how to nicely change BPM
            // if (score % 2 == 0)
            //     conductor.SetBpm(conductor.GetBpm()+10);
            printf("%f, Perfect\n", current_beat);
        }
    }

    // Missed beat
    if (
        (current_beat > int_beat + e) &&
        (int_beat != last_beat_tapped) &&
        (int_beat % 3 == 0)
    ) {
        Lose();
    }


    // Update children
    Scene::Update();
}

void Metrohop::Draw(){
    ClearBackground(BLACK);

    // Draw score
    char s[12] = {0};
    sprintf(s, "Score: %d", score);
    float width = MeasureText(s, 24);
    DrawText(s, 800/2 - width/2, 0, 24, WHITE);
    
    // Draw lights
    for (auto child : children) {
        child->Draw();
    }
}