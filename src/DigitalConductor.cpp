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

// void DigitalConductor::SetBpm(float bpm){
//     this->bpm = bpm;
//     crotchet = 60/bpm;
//     // BUG: This will cause errors if not done exactly on beat!
//     elapsed_time = 0;
// }

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

int DigitalConductor::GetIntegerBeat() {
    return (int) (elapsed_time * bpm / 60.0f);
}

float DigitalConductor::GetFractionalBeat() {
    float beat = elapsed_time * bpm / 60.0f;
    return beat - (int) beat;
}