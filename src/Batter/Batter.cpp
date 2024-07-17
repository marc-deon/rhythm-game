#include "Batter/Batter.hpp"
#include <stdio.h>
#include "DrawTextureTiled.hpp"

#define VIRT_SCREEN_W 800
#define VIRT_SCREEN_H 600

Batter::Batter() {
    texture = LoadTexture("graphics/baseball/batter.png");
}

Batter::~Batter() {
    UnloadTexture(texture);
}

void Batter::Anim_Reset() {
    frame = 0;
    wait = 0;
    playing = false;
}

void Batter::Draw() {
    float scale = 2;

    Rectangle source = size;
    source.x = size.width * frame;
    float x = VIRT_SCREEN_W / 2;
    float y = (VIRT_SCREEN_H / 2) - (scale * size.height / 2) + 125;

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
        frame++;
        wait -= frames_to_wait;
        if (frame == frame_count)
            Anim_Reset();
    }
}

void Batter::Swing() {
    playing = true;
}
