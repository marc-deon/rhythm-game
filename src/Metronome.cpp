#include "Metronome.hpp"
#include "stdio.h"

Metronome::~Metronome() {
    printf("UNLOAD METRONOME 1\n");
    UnloadSound(sound);    
}

Metronome::Metronome(Conductor* c, int beats_per_measure, float offset) {
    this->offset = offset;
    this-> beats_per_measure = beats_per_measure;
    lastbeat = offset;
    conductor = c;

    sound = LoadSound("sfx/metronome.wav");
}

int Metronome::Update(){
    float crotchet = conductor->GetCrotchet();
    if (conductor->GetSongTimePosition() > lastbeat + crotchet) {
        if ((int)conductor->GetSongBeatPosition() % beats_per_measure == 0) {
            SetSoundPitch(sound, 1.1f);
            PlaySound(sound);
        }
        else{
            SetSoundPitch(sound, 1.0f);
            PlaySound(sound);
        }
        lastbeat += crotchet;
    }
    return 0;
}

void Metronome::Draw() {}