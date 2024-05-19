#pragma once

class Conductor {
    protected:
    float bpm;
    float crotchet;  // Length of quarter note

    public:

    // Position of song in seconds
    float virtual GetSongTimePosition() = 0;
    // Position of song in beats
    float virtual GetSongBeatPosition() = 0;
    // Integer portion of song time position
    int virtual GetInteger() = 0;
    // Fractional portion of song time position
    float virtual GetFractional() = 0;
    // Beats per minute
    float virtual GetBpm() {return bpm;}
    // Set the BPM and crotchet.
    void virtual SetBpm(float bpm) {this->bpm = bpm; crotchet = 60/bpm;};
    // Length of quarter note
    float virtual GetCrotchet() {return crotchet;}

    void virtual Update() = 0;
    void virtual Start() = 0;
    void virtual Pause() = 0;
    void virtual Resume() = 0;
    
};
