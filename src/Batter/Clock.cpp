#include "Batter/Clock.hpp"
#include "stdio.h"

Clock::Clock(Conductor* c, float offset) {
    texture = LoadTexture("graphics/baseball/clock.png");

    lastbeat = offset;
    this->offset = offset;
    conductor = c;
}

void Clock::SetOffset(float x) {
    lastbeat = offset = x;
}

Clock::~Clock() {
    UnloadTexture(texture);
}

void Clock::Update() {
    if (conductor->GetSongTimePosition() > lastbeat) {
        lastbeat += conductor->GetCrotchet();
        if (swingDirection == SWING_LEFT) {
            SwingRight();
        }
        else {
            SwingLeft();
        }
    }
}

void Clock::Draw() {
    float scale = 2;

    Rectangle source = size;
    source.x = size.width * frame;
    // Draw the clock a bit to the right of the batter
    float x = GetScreenWidth() / 2 + source.width * 2;
    float y = (GetScreenHeight() / 2) - (scale * size.height / 2);

    DrawTexturePro(texture,
        source,
        {x, y, size.width * scale, size.height * scale},
        {0, 0},     // Origin
        0,          // Rotation
        WHITE
    );

    if (!playing)
        return;

    wait += 60.0 / GetFPS();

    if(((int)wait) >= frames_to_wait) {
        // Swinging right is the first half of the spritesheet, and swinging left is the second half
        int final_frame = swingDirection == SWING_LEFT ? 9 : 4;

        if (frame == final_frame) {
            playing = false;
            wait = 0;
        }
        else {
            frame++;
            wait -= frames_to_wait;
        }
    }
}

void Clock::SwingLeft() {
    frame = 5;
    playing = true;
    swingDirection = SWING_LEFT;
}

void Clock::SwingRight() {
    frame = 0;
    playing = true;
    swingDirection = SWING_RIGHT;
}