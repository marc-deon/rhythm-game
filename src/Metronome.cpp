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

    printf("metronome bpm is %d\n", beats_per_measure);
    sound = LoadSound("sfx/metronome.wav");
}

void Metronome::Update(){
    float crotchet = conductor->GetCrotchet();
    if (conductor->GetSongTimePosition() > lastbeat + crotchet) {
        if (((int)conductor->GetSongBeatPosition() % beats_per_measure) == 0) {
            SetSoundPitch(sound, 1.1f);
            PlaySound(sound);
            printf("Play 1.1\n");
        }
        else{
            SetSoundPitch(sound, 1.0f);
            PlaySound(sound);
            printf("Play 1.0\n");
        }
        lastbeat += crotchet;
    }
}

void Metronome::Draw() {}