#include "StreamConductor.hpp"
#include <stdio.h>

StreamConductor::StreamConductor(char* filename, float bpm){
    stream = LoadMusicStream(filename);
    stream.looping = false;
    // SetMusicVolume(stream, 0);
    if (bpm != -1)
        SetBpm(bpm);
    // offset = 0;
}

void StreamConductor::SetBpm(float bpm) {
    this->bpm = bpm;
    crotchet = 60.0f / bpm;
}

// void StreamConductor::SetOffset(float offset) {
//     this->offset = offset;
// }

StreamConductor::StreamConductor(){ }
StreamConductor::~StreamConductor(){
    UnloadMusicStream(stream);
}

float StreamConductor::GetBpm() {
    return bpm;
}

float StreamConductor::GetCrotchet() {
    return crotchet;
}

// float StreamConductor::GetOffset() {
//     return offset;
// }

float StreamConductor::GetSongTimePosition() {
    // return GetMusicTimePlayed(stream) - offset;
    return GetMusicTimePlayed(stream);
}

float StreamConductor::GetSongBeatPosition() {
    return GetSongTimePosition() * bpm / 60.0f;
}

Music StreamConductor::GetStream(){
    return stream;
}

bool StreamConductor::IsPlaying(){
    return IsMusicStreamPlaying(stream);
}

void StreamConductor::Update(){
    UpdateMusicStream(stream);
}

void StreamConductor::Start(){
    PlayMusicStream(stream);
}

void StreamConductor::Pause(){
    PauseMusicStream(stream);
}

void StreamConductor::Resume(){
    ResumeMusicStream(stream);
}

void StreamConductor::ChangeVolume(float x){
    volume = volume + x > 1 ? 1 : volume + x;
    SetMusicVolume(stream, volume);
}

void StreamConductor::SetVolume(float x){
    volume = x;
    SetMusicVolume(stream, volume);
}

int StreamConductor::GetInteger() {
    return (int)GetSongTimePosition();
}

float StreamConductor::GetFractional() {
    return GetSongTimePosition() - (int)GetSongTimePosition();
}
