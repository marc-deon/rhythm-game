#pragma once

struct Beatmap_Note_Type;
struct Beatmap_Note;

struct Beatmap_Note_Type {
    int main; // Cue, note, song end...
    int sub;  // Left button, right button, hold, release...
    // Beatmap_Note* note;
};

// TODO: Probably make a subclass of events (also make an event struct)
struct Beatmap_Note {
    float seconds; // time to trigger this note
    Beatmap_Note_Type type;
    bool triggered = false;  // Whether this has popped up for the beatmap yet
    bool tapped = false; // Whether this has been tapped by the player yet
};

