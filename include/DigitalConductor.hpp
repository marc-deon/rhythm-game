#pragma once
#include "Conductor.hpp"

class DigitalConductor : public Conductor {
    private:
    float elapsed_time;
    float lastbeat;

    public:
    DigitalConductor();
    ~DigitalConductor();

    float GetSongTimePosition() override;
    float GetSongBeatPosition() override;
    void Update() override;
    void Start() override;
    void Pause() override;
    void Resume() override;
    int GetInteger() override;
    float GetFractional() override;
    // void SetBpm(float bpm) override;

};
