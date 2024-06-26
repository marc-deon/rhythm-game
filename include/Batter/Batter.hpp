#pragma once
#include "StreamConductor.hpp"
#include "SceneObject.hpp"

class Batter : public SceneObject {
private:
    Texture texture;
    Rectangle size = {0, 0, 109, 129};     // Width and height of a single drawing
    int frame = 0;          // Current drawing number
    int frame_count = 5;    // Number of drawings
    // TODO: Decouple this from framerate
    int frames_to_wait = 2; // Wait this many engine frames to display the next drawing
    float wait = 0;           // Current wait
    bool playing = false;
    void Anim_Reset();

public:
    Batter();
    ~Batter();
    void Draw();
    void Swing();
};

