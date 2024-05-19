#include "Metrohop.hpp"
#include "Metronome.hpp"
#include "Metro_Light.hpp"

Metrohop::Metrohop() {
    name = "Metrohop";

    conductor.SetBpm(100);

    children.push_back(new Metro_Light(&conductor, GREEN, DARKGREEN, 1));
    children.push_back(new Metro_Light(&conductor, YELLOW, ORANGE, 2));
    children.push_back(new Metro_Light(&conductor, RED, DARKRED, 3));
    children.push_back(new Metronome(&conductor, 3));

}

void Metrohop::Update() {
    conductor.Update();

    // Update all children
    Scene::Update();
}

// void Metrohop::Draw() {
//     Scene::Draw();
// }