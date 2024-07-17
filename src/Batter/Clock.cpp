#include "Batter/Clock.hpp"
#include "stdio.h"

#define VIRT_SCREEN_W 800
#define VIRT_SCREEN_H 600

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
    float x = VIRT_SCREEN_W / 2 + source.width * 2 - 40;
    float y = (VIRT_SCREEN_H / 2) - (scale * size.height / 2) + 85;

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
        int final_frame = swingDirection == SWING_LEFT ? frame_count*2-1 : frame_count-1;


        if (frame == final_frame) {
            playing = false;
            wait = 0;
        }
        else {
            frame++;
            // Apex frames; slow animation
            if (frame == 2 || frame == 7)
                frames_to_wait = 4;
            wait -= frames_to_wait;
        }
    }
}

void Clock::SwingLeft() {
    frames_to_wait = 2;
    frame = frame_count;
    playing = true;
    swingDirection = SWING_LEFT;
}

void Clock::SwingRight() {
    frames_to_wait = 2;
    frame = 0;
    playing = true;
    swingDirection = SWING_RIGHT;
}