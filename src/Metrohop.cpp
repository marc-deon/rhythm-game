#include "Metrohop.hpp"
#include "Metronome.hpp"
#include "Metro_Light.hpp"
#include "SceneManager.hpp"

// Use negatives for early
#define HIT_PERFECT 1
#define HIT_GOOD 2
#define HIT_BAD 3

Metrohop::~Metrohop() {
    for(auto c : children) {
        delete c;
    }
    children.clear();
    printf("metrohop deconstructed\n");
}

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

void Metrohop::Lose() {
    display_score_screen = true;
}

void Metrohop::DisplayScoreScreen() {
    int x, y;    // Location of various texts
    char sp[12]; // perfect string
    char sg[12]; // great string
    sprintf(sp, "%d PERFECTS", score_perfect);
    sprintf(sg, "%d GOODS", score_good);

    // Center horizontally
    x = 800/2 - MeasureText("YOU SCORED:", 36)/2;
    // Place a fifth down the screen
    y = 600/5 - 36/2;
    // Draw text, with about 12 pixels between each line
    DrawText("YOU SCORED:", x, y, 36, WHITE);
    DrawText(sp, x, y+=48, 24, WHITE);
    DrawText(sg, x, y+=36, 24, WHITE);

    // Get the starting point
    x = 800 - 20 - MeasureText("PRESS Z TO CONTINUE", 16);
    y = 600 - 20 - 16;
    // Draw partial text                        Update horizontal
    DrawText("PRESS ", x, y, 16, WHITE);        x += MeasureText("PRESS ", 16);
    DrawText("Z", x, y, 16, GREEN);             x += MeasureText("Z", 16);
    DrawText(" TO CONTINUE", x, y, 16, WHITE);

}

void Metrohop::Update() {

    if (display_score_screen) {
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

    if (IsKeyPressed(KEY_END)) {
        SceneManager::ReplaceScene(SCENE_MAINMENU);
        return;
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
        else {
            last_beat_tapped = attempt > 0 ? int_beat : int_beat+1;
            score_perfect += abs(attempt) == HIT_PERFECT;
            score_good += abs(attempt) == HIT_GOOD;
            // TODO: Figure out how to nicely change BPM
            // Maybe instead of doing elaspsed_time, we have elapsed_beats as our fundamental?
            // if (score % 2 == 0)
            //     conductor.SetBpm(conductor.GetBpm()+10);
            printf("%f, OK\n", current_beat);
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

    if (display_score_screen) {
        DisplayScoreScreen();
        return;
    }

    // Draw score
    char s[12] = {0};
    sprintf(s, "Score: %d", score_good + score_perfect);
    float width = MeasureText(s, 24);
    DrawText(s, 800/2 - width/2, 0, 24, WHITE);
    
    // Draw lights
    for (auto child : children) {
        child->Draw();
    }
}