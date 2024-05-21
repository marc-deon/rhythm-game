#pragma once

#include "Conductor.hpp"
#include "SceneObject.hpp"

class RhythmObject : public SceneObject {
    public:
    Conductor* conductor;
    int virtual Update() override {return 0;};
    
};