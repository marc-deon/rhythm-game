#pragma once
#include <raylib.h>
#include <StreamConductor.hpp>
#include "RhythmObject.hpp"

class Metronome : public RhythmObject {
private:
    Conductor* conductor;
    float lastbeat;
    float offset;
    Sound sound;
    int beats_per_measure;

public:
    Metronome(Conductor* conductor, int beats_per_measure=4, float offset=0);
    ~Metronome();

    void Update() override;
    void Draw() override;
};


