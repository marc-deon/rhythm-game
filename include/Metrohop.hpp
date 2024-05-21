#include "Scene.hpp"
#include <raylib.h>
#include "Conductor.hpp"
#include "DigitalConductor.hpp"
#include "RhythmObject.hpp"

class Metrohop : public Scene {
    private:
    bool display_score_screen = false;
    int score_perfect = 0;
    int score_good = 0;
    int last_beat_tapped = 0;
    DigitalConductor conductor;

    void DisplayScoreScreen(); // After player loses, swap to a subscene that just shows score
    void Lose();
    void Exit(); // Aftter viewing score, tear down and go back to main menu
    float GetErrorRange();
    int CheckInRange();

    public:
    int Update() override;
    void Draw() override;
    Metrohop();
    ~Metrohop();

};