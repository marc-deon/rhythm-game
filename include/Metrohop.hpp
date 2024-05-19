#include "Scene.hpp"
#include <raylib.h>
#include "Conductor.hpp"
#include "DigitalConductor.hpp"
#include "RhythmObject.hpp"

class Metrohop : public Scene {
    private:
    int score;
    void DisplayScore(); // After player loses, swap to a subscene that just shows score
    void Exit(); // Aftter viewing score, tear down and go back to main menu
    DigitalConductor conductor;

    public:
    void Update() override;
    // void Draw() override;
    Metrohop();

};