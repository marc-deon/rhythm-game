#include "DigitalConductor.hpp"
#include <raylib.h>

DigitalConductor::DigitalConductor() {
    elapsed_time = 0;
}

DigitalConductor::~DigitalConductor() {
}

float DigitalConductor::GetSongTimePosition() {
    return elapsed_time;
}

float DigitalConductor::GetSongBeatPosition() {
    return elapsed_time * bpm / 60.0f;
}

// If this drifts over time, we could also try using Raylib::GetTime() and subtracting the start time
void DigitalConductor::Update() {
    elapsed_time += GetFrameTime();
    
}

void DigitalConductor::Start() {

}

void DigitalConductor::Pause() {

}

void DigitalConductor::Resume() {

}

int DigitalConductor::GetInteger() {
    return (int) elapsed_time;
}

float DigitalConductor::GetFractional() {
    return elapsed_time - (int) elapsed_time;
}
