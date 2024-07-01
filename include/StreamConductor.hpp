#pragma once
#include <raylib.h>
#include "Conductor.hpp"

class StreamConductor : public Conductor {

private:
    Music stream;
    float volume = 1.0;
    float offset;    // mp3 only?

public:
    StreamConductor();
    StreamConductor(char* filename, float bpm=-1);
    ~StreamConductor();
    float GetBpm();
    float GetCrotchet();
    float GetSongTimePosition();
    float GetSongBeatPosition();
    Music GetStream();
    bool IsPlaying();
    void Update();
    void Start();
    void Pause();
    void Resume();
    void ChangeVolume(float x);
    void SetVolume(float x);
    int GetInteger();
    float GetFractional();
    void SetBpm(float bpm);
};
