#include "Metro_Light.hpp"
#include "stdio.h"

Metro_Light::Metro_Light(Conductor* c, Color active, Color inactive, float beat) {
    conductor = c;
    color_active = active;
    color_inactive = inactive;
    this->beat = beat;
}


void Metro_Light::Draw() {
    float crotchet = conductor->GetCrotchet();

    int curbeat = (int) conductor->GetSongBeatPosition();
    color_current = ((curbeat % 3) + 1 == beat) ? color_active : color_inactive;
    
    const float w = 100;
    const float h = 150;
    float half = 800/2;
    float pos = beat - 2;
    float x = half - w/2 + 800 / 4 * pos;
    float y = 600 * 10.f/30.f - h;
    DrawRectangle(x, y, w, h, color_current);
}

void Metro_Light::Update() {

}