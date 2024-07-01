#pragma once
#include "StreamConductor.hpp"
#include "SceneObject.hpp"

enum SwingDirection {
    SWING_LEFT,
    SWING_RIGHT
};

class Clock : public SceneObject {
private:
    Texture texture;
    Rectangle size = {0, 0, 73, 113};     // Width and height of a single drawing
    int frame = 0;          // Current drawing number
    int frame_count = 5;    // Number of drawings
    // TODO: Decouple this from framerate
    int frames_to_wait = 2; // Wait this many engine frames to display the next drawing
    float wait = 0;           // Current wait
    bool playing = false;
    SwingDirection swingDirection = SWING_RIGHT;
    Conductor* conductor;
    float lastbeat;
    float offset;

public:
    Clock(Conductor* c, float offset=0);
    ~Clock();
    void SwingLeft();
    void SwingRight();
    void Draw();
    void Update();
    void SetOffset(float offset);
};

